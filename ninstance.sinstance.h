/* defines ninstance::sinstance member functions */

#pragma once

using namespace std;

namespace ninstance {
	sinstance::sinstance() {
		insts = 0;
		accumulators = 0;
		filters = 0;
		instcount = 0;
		filtercount = 0;
	}

	sinstance::~sinstance() {
		free();
	}

	void sinstance::free() {
		delete [] insts;
		delete [] accumulators;
		for (int i = 0; i < filtercount; ++i) delete filters[i];
		delete [] filters;
		insts = 0;
		filters = 0;
		accumulators = 0;
		instcount = 0;
		filtercount = 0;
	}

	void sinstance::render(const double time) {
		if (!insts || !accumulators) return;

		nregister::zero0();

		if (time < instduration) {
			for (int i = 0; i < instcount; ++i) {
				nclip::clip(time, insts[i], accumulators[i]);
			}
		}

		if (time < filterduration) {
			for (int i = 0; i < filtercount; ++i) filters[i]->filter(nregister::localreg[0], nregister::localreg[0], nregister::len);
		}
	}
}