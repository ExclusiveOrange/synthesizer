/* defines nlowlevel::fill functions

validated

*/

#pragma once

namespace nlowlevel {
	void fill (
		double *dest
		,const int len
		,const double val
	) {
		for (int i = 0; i < len; ++i) {
			dest[i] = val;
		}
	}
}