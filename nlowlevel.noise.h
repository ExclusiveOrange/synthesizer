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
		for( int i = 0; i < len; i++ ) {
			dest[ i ] = nrandom::uniform( low, high );
		}
	}
}