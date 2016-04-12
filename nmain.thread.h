/* defines nmain thread functions */

#pragma once

namespace nmain {
	CRITICAL_SECTION csoutputstack;
	double **outputstack = 0;
	unsigned int outputstackmax;

	__declspec(thread) double *output;

	void initproc() {
		EnterCriticalSection(&csoutputstack);
		output = outputstack[outputstackmax++];
		LeaveCriticalSection(&csoutputstack);
	}

	void workproc_clear(void *arg) {
		#pragma warning(disable : 810) // conversion from "void *" to "unsigned int" may lose significant bits
		unsigned int ithread = (unsigned int)arg;
		#pragma warning(default : 810)
		for (unsigned int s = 0; s < nregister::len * numchannels; ++s) {
			outputstack[ithread][s] = 0.0;
		}
	}

	void workproc_listen(void *arg) {
		nlistener::clistener *listener = (nlistener::clistener*)arg;
		listener->listen(output);
	}

	void stopproc() {
		EnterCriticalSection(&csoutputstack);
		outputstackmax--;
		LeaveCriticalSection(&csoutputstack);
	}

	bool initoutputstack() {
		outputstack = new double*[numthreads];
		if (outputstack) {
			unsigned int numoutputstack = 0;
			for (; numoutputstack < numthreads; ++numoutputstack) {
				double *newoutput = new double[nregister::len * numchannels];
				if (!newoutput) break;
				outputstack[numoutputstack] = newoutput;
			}
			if (numoutputstack == numthreads) {
				for (int t = 0; t < numthreads; ++t) {
					for (int i = 0; i < nregister::len * numchannels; ++i) {
						outputstack[t][i] = 0.0;
					}
					//ippsZero_64f(outputstack[t], nregister::len * numchannels);
				}
				InitializeCriticalSection(&csoutputstack);
				outputstackmax = 0;
				return true;
			}
			while (numoutputstack) delete [] outputstack[--numoutputstack];
			delete [] outputstack;
			outputstack = 0;
		}
		return false;	
	}

	void freeoutputstack() {
		DeleteCriticalSection(&csoutputstack);
		if (outputstack) {
			for (unsigned int i = 0; i < numthreads; ++i) {
				delete outputstack[i];
			}
			delete outputstack;
			outputstack = 0;
		}
	}
}