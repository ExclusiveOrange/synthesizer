/* defines namespace nmain */

#pragma once

#include <conio.h>
#include <memory.h>
#include <process.h>
#include <stdio.h>

#include "helper.h"
#include "ninstance.h"
#include "nlistener.h"
#include "naudiodevice.h"
#include "nmultithread.h"

using namespace std;

namespace nmain {
	unsigned int rate;
	unsigned int numthreads = 0;
	unsigned int maxworkstacksize;
	unsigned int numchannels = 0;
	unsigned int regsperbuffer;
	unsigned int bufferlen;
	unsigned int numbuffers;
	unsigned int curbuf;
	float *buffers = 0;
}

#include "nmain.thread.h"

namespace nmain {
	bool init() {
		rate = 96000; // let's be reasonable until we can savagely optimize everything
		numthreads = 0; // 0 allows this to default
		maxworkstacksize = 65536; // somewhat arbitrary

		//init_intel();
		nrandom::init();
		//numthreads = numthreads ? numthreads : ippGetNumCoresOnDie(); // not using intel stuff anymore
		numthreads = 8; // TODO: detect number of virtual cores available, use them all

		nlowlevel::init();
		
		if (naudiodevice::init(rate)) {
			numchannels = naudiodevice::voicedetails.InputChannels;
			regsperbuffer = (1 + (rate / nregister::len)) / 4;
			bufferlen = regsperbuffer * nregister::len;
			numbuffers = 3;

			buffers = new float[numbuffers * bufferlen * numchannels];
			if (buffers) {
				curbuf = 0;

				if (initoutputstack()) {

					if (nmultithread::init(numthreads, maxworkstacksize, initproc/*, workproc_listen*/, stopproc)) {

						nregister::rate = (double)rate;
						nregister::rrate = 1.0 / nregister::rate;
						nregister::duration = (double)nregister::len * nregister::rrate;
						return true;

						nmultithread::stop();
					} else cerr << "nmultithread::init() failed.\n";

					freeoutputstack();
				} else cerr << "couldn't allocate memory for outputstack.\n";

				delete [] buffers;
				buffers = 0;
			} else cerr << "couldn't allocate memory for audio device buffers.\n";

			naudiodevice::free();
		} else cerr << "naudiodevice::init() failed.\n";

		cerr << "Press any key to continue . . .\n";
		#pragma warning(suppress: 6031)
		_getch();
		return false;
	}

	void free() {
		nmultithread::stop();
		freeoutputstack();
		delete [] buffers;
		buffers = 0;
		naudiodevice::free();
	}
}