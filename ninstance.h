/* defines namespace ninstance */

#pragma once

#include "nclip.h"
#include "nfilter.h"
#include "nrpngen.h"

namespace ninstance {
	struct sinstance {
		double instduration;
		double filterduration;

		ninstruction::sinst *insts;
		nclip::uacc *accumulators;
		nfilter::cfilter **filters;

		int instcount;
		int filtercount;

		sinstance();
		~sinstance();
		void free();
		void render(const double time);
	};

	sinstance *instantiate(nrpngen::srpnsource *source);
}

#include "ninstance.sinstance.h"
#include "ninstance.instantiate.h"