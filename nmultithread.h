/* defines namespace nmultithread */

#pragma once

#include <windows.h>

namespace nmultithread {

	const DWORD idlecheckperiod = 50; // when idling, workerthread checks 'stopwork' every this many milliseconds while waiting for work

	// workerthread will call these as appropriate
	void (*initproc)();
	void (*workproc)(void *work);
	void (*stopproc)();

	// thread handles
	HANDLE *phthread;
	unsigned int numthreads;

	// event handles
	HANDLE hwork; // signaled by the consumer when there is work to do
	HANDLE hidle; // signaled by the worker when it decrements busyworkers to 0

	// work stack
	CRITICAL_SECTION csworkstack;
	void **workstack;
	unsigned int maxworkstacksize;
	unsigned int workstacksize;

	CRITICAL_SECTION csworkunfinished;
	unsigned int workunfinished;

	bool stopwork; // set true by consumer when worker threads should exit

	DWORD WINAPI workerthread(void *arg) {
		initproc();
		for (;;) {
			DWORD result;
			do {
				if (stopwork) {
					stopproc();
					return 0;
				}
				result = WaitForSingleObject(hwork, idlecheckperiod);
			} while (result == WAIT_TIMEOUT);
			unsigned int workcompleted = 0;
			for (;;) {
				void *work;
				EnterCriticalSection(&csworkstack);
				if (workstacksize) {
					work = workstack[--workstacksize];
					LeaveCriticalSection(&csworkstack);
				} else {
					ResetEvent(hwork);
					LeaveCriticalSection(&csworkstack);
					break;
				}
				workproc(work);
				workcompleted++;
			}
			if (workcompleted) {
				EnterCriticalSection(&csworkunfinished);
				if (!(workunfinished -= workcompleted)) SetEvent(hidle);
				LeaveCriticalSection(&csworkunfinished);
			}
		}
	}

	bool addwork(void *work) {
		bool result = true;
		EnterCriticalSection(&csworkunfinished);
		if (!workunfinished++) ResetEvent(hidle);
		LeaveCriticalSection(&csworkunfinished);
		EnterCriticalSection(&csworkstack);
		if (workstacksize < maxworkstacksize) {
			workstack[workstacksize++] = work;
			SetEvent(hwork);
		} else result = false;
		LeaveCriticalSection(&csworkstack);
		return result;
	}

	bool init (
		unsigned int numthreads
		,unsigned int maxworkstacksize
		,void (*initproc)()
		,void (*stopproc)()
	) {
		nmultithread::numthreads = numthreads;
		nmultithread::initproc = initproc;
		nmultithread::stopproc = stopproc;
		hwork = CreateEvent(0, TRUE, FALSE, 0);
		if (hwork) {
			hidle = CreateEvent(0, TRUE, TRUE, 0);
			if (hidle) {
				phthread = new HANDLE[numthreads];
				if (phthread) {
					workstack = new void*[maxworkstacksize];
					if (workstack) {
						nmultithread::maxworkstacksize = maxworkstacksize;
						workstacksize = 0;
						InitializeCriticalSection(&csworkunfinished);
						InitializeCriticalSection(&csworkstack);
						stopwork = false;
						unsigned int createdthreads = 0;
						for (; createdthreads < numthreads; ++createdthreads) {
							if (!(phthread[createdthreads] = CreateThread(0, 0, workerthread, 0, 0, 0))) break;
						}
						if (createdthreads == numthreads) {
							return true;
						}
						while (createdthreads) CloseHandle(phthread[--createdthreads]);
						DeleteCriticalSection(&csworkstack);
						DeleteCriticalSection(&csworkunfinished);
						delete [] workstack;
						workstack = 0;
						nmultithread::maxworkstacksize = 0;
					}
					delete [] phthread;
					phthread = 0;
				}
				CloseHandle(hidle);
				hidle = 0;
			}
			CloseHandle(hwork);
			hwork = 0;
		}
		return false;
	}

	void stop() {
		stopwork = true;
		{	unsigned int iwaitthread = numthreads;
			while (iwaitthread > MAXIMUM_WAIT_OBJECTS) {
				iwaitthread -= MAXIMUM_WAIT_OBJECTS;
				WaitForMultipleObjects(MAXIMUM_WAIT_OBJECTS, phthread + iwaitthread, TRUE, INFINITE);
			}
			WaitForMultipleObjects(iwaitthread, phthread, TRUE, INFINITE);
		}
		while (numthreads) CloseHandle(phthread[--numthreads]);
		DeleteCriticalSection(&csworkstack);
		DeleteCriticalSection(&csworkunfinished);
		delete [] workstack;
		workstack = 0;
		maxworkstacksize = 0;
		workstacksize = 0;
		delete [] phthread;
		phthread = 0;
		CloseHandle(hidle);
		hidle = 0;
		CloseHandle(hwork);
		hwork = 0;
	}

	bool waitforidle(DWORD milliseconds) { // can use INFINITE if you want
		DWORD result = WaitForSingleObject(hidle, milliseconds);
		return result == WAIT_OBJECT_0 ? true : false;
	}
}