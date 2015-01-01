/* defines nlowlevel::line functions */

#pragma once

namespace nlowlevel {
	void line (
		double *dest
		,const int len
		,const double offset
		,const double slope
	) {
		for (int i = 0; i < len; ++i) {
			dest[i] = offset + slope * (double)i;
		}
	}
}