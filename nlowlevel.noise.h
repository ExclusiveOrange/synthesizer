/* defines nlowlevel::noise functions

validated

requires:
	"nrandom.h"
	have called nrandom::init()

*/

#pragma once

namespace nlowlevel {
	void noise (
		double *dest
		,const int len
		,const double low
		,const double high
	) {
		nrandom::uniform(dest, len, low, high);
	}
}