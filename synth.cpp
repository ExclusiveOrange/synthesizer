/* Naming Convention

	nname
		namespace
	sname
		struct
	uname
		union
	name
		variable or function
*/

/* Function Declaration

	// one or fewer parameters
	void name(double parameter) {
		do;
		stuff;
		here;
	}

	// two or more parameters
	// notice the space between name and opening parenthesis
	void name (
		double *parameter // description
		,int parameter // description
		,char *parameter // description
	) {
		do;
		stuff;
		here;
	}

Alternate Formatting (seems to be easier to read):

	// any number of parameters
	void
	name (
		parameter
		, another parameter
		, last parameter
	) {
		do;
		stuff;
		here;
	}
*/

// make certain we are compiling with the correct SDK
#define WINVER 0x0601
#define _WIN32_WINNT 0x0601
#define NTDDI_VERSION 0x06010000

#include "nmain.h"

//#include "test.h"

#include <cstdio> // may want to add to nmain.h
#include <list>

using namespace nmain;

typedef list<nlistener::clistener*> tdlistenerstack;
tdlistenerstack listenerstack;

nlistener::sear *makeears() {
	nlistener::sear *ears = new nlistener::sear[numchannels];
	if (ears) {
		switch (numchannels) {
			case 1:
				ears[0].set(0.0, 0.0, 0.0, 1.0, M_PI, 1.0, 0.0, 0.0);
				break;
			case 2:
				ears[0].set (
					-0.1123, 0.0
					,-M_PI2, 1.0
					,M_PI2 * 0.3, 0.8
					,M_PI2 * 0.35, 0.3
				);
				ears[1].set (
					0.1123, 0.0
					,M_PI2, 1.0
					,M_PI2 * 0.3, 0.8
					,M_PI2 * 0.35, 0.3
				);
				break;
			default:
				for (int e = 0; e < numchannels; ++e) {
					ears[e].set(0.0, 0.0, 0.0, 1.0, M_PI, 1.0, 0.0, 0.0);
				}
		}
		return ears;
	}
	return 0;
}

void combinethreadoutput(float *output) {
	for (unsigned int s = 0; s < nregister::len; ++s) {
		for (unsigned int c = 0; c < numchannels; ++c) {
			double acc = 0.0;
			for (unsigned int t = 0; t < numthreads; ++t) {
				acc += outputstack[t][c * nregister::len + s];
			}
			output[s * numchannels + c] = acc < -1.0 ? -1.0f : acc > 1.0 ? 1.0f : (float)acc;
		}
	}
}

int main(int argc, char *argv[]) {
	if (init()) {

		nrpngen::crpngen rpngen;
		rpngen.set_instnames();
		rpngen.set_regnames(nregister::num);

		// crude hack to use first command line parameter as name of file to open
		char *filename = "test.soundlanguagesource"; // default
		if(argc > 1 && argv[1]) {
			filename = argv[1];
		}
		
		// crude hack to use second command line parameter as number of sources to add per second
		double newprobability = 1000.0; // default for performance profiling
		if(argc > 2 && argv[2]) {
			// somewhat arbitrary limits
			float minnewprobability = 1.0f / 1048576.0f;
			float maxnewprobability = 1048576.0f;
			float scannednewprobability = (float)newprobability;
			int ret = sscanf(argv[2], "%f", &scannednewprobability);
			if(ret == 1) {
				scannednewprobability = max(minnewprobability, scannednewprobability);
				scannednewprobability = min(maxnewprobability, scannednewprobability);
				newprobability = (double)scannednewprobability;
			}
		}

		nrpngen::srpnsource *rpnsource = nrpngen::getrpnsource(rpngen, filename);
		if (rpnsource) {

			nlistener::sear *ears = makeears();
			if (ears) {

				//double newprobability = 20.0; // average number of sources added per second
				double radius = 40.0;
				double minradius = 5.0;
				double minx = -radius;
				double miny = -radius;
				double maxx = radius;
				double maxy = radius;
				double mindistance = 1.0;
				
				// temporary
				unsigned int maxlisteners = 0;

				cout << "Playback begins.\nPress any key to quit.\n";

				bool quit = false;
				while (!quit) {
					// set current buffer pointer
					float *buf = buffers + curbuf * bufferlen * numchannels;

					for (unsigned int i = 0; i < regsperbuffer; ++i) {
						// render all listeners
						maxlisteners = max(listenerstack.size(), maxlisteners);
						if (listenerstack.size()) {
							nmultithread::workproc = nmain::workproc_listen;
							tdlistenerstack::const_iterator iter = listenerstack.begin();
							do {
								nmultithread::addwork(*iter);
							} while (++iter != listenerstack.end());
						}
						printf("Listeners: %d          \r", (int)listenerstack.size());

						// add new listeners
						{ int newcount = /*newprobability * nregister::duration;*/(int)nrandom::uniform(0.0, 1.0 + newprobability * nregister::duration);
							for (; newcount > 0; --newcount) {
								nlistener::clistener *listener = new nlistener::clistener;
								if (listener) {
									ninstance::sinstance *instance = ninstance::instantiate(rpnsource);
									if (instance) {
										double x, y;
										do {
											x = nrandom::uniform( minx, maxx );
											y = nrandom::uniform( miny, maxy );
										} while( sqrt( x * x + y * y ) < minradius );
										double time = nrandom::uniform( -nregister::duration, 0.0 );
										if (listener->init(numchannels, ears, time, instance, x, y, mindistance)) {
											listenerstack.push_back(listener);
										} else delete instance;
									} else delete listener;
								}
							}
						}

						// mix all thread outputs and convert to float
						nmultithread::waitforidle(INFINITE);
						combinethreadoutput(buf + i * nregister::len * numchannels);

						// clear all thread outputs
						nmultithread::workproc = nmain::workproc_clear;
						for (unsigned int t = 0; t < numthreads; ++t) {
							nmultithread::addwork((void*)t);
						}

						// remove old listeners
						if (listenerstack.size()) {
							tdlistenerstack::iterator iter = listenerstack.begin();
							do {
								if ((*iter)->expired) {
									delete *iter;
									iter = listenerstack.erase(iter);
								} else iter++;
							} while (iter != listenerstack.end());
						}

						// wait for the clear operation to finish
						nmultithread::waitforidle(INFINITE);
					}

					quit = _kbhit() != 0;

					if (quit) { // fade out final buffer
						int is = bufferlen - 1;
						float fi = 1.0f / (float)is;
						for (int s = 0; s < bufferlen; ++s, --is) {
							float f = (float)is * fi;
							for (int c = 0; c < numchannels; ++c) {
								buf[s * numchannels + c] *= f;
							}
						}
					}

					naudiodevice::waitonbuffers(numbuffers, INFINITE);
					naudiodevice::submitbuffer(buf, bufferlen, quit);

					curbuf++;
					curbuf %= numbuffers;
				}
				switch (_getch()) {
					case 0x00:
					case 0xE0:
						#pragma warning(suppress: 6031)
						_getch();
						break;
				}
				cout << endl;
				cout << "Waiting for audio device to finish...\n";
				naudiodevice::waitonend(INFINITE);
				cout << "Playback ended.\n";
				
				printf("maximum simultaneous listeners: %u\n", maxlisteners);

				delete [] ears;
			} else cerr << "makeears() failed.\n";

			delete rpnsource;
			rpnsource = 0;
		} else cerr << "nrpngen::getrpnsource() failed.\n";

		free();
	}
	return 0;
}