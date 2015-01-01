/* defines nlowlevel::exp functions

requires:
	<math.h>

description:
	exp *dest, len, *src

	dest[i] = exp(a[i])

*/

#pragma once

#include <math.h>

namespace nlowlevel {
	void exp (
		double *dest
		,const int len
		,const double *src
	) {
		double src1 = src[ 0 ];
		for (int i = 0; i < len; ++i) {
			dest[i] = ::exp(src1);
			src1 = src[ i + 1 ];
		}
	}
}		