#pragma once

#include "restrict.h"

namespace nlowlevel {
	void
	fastcopy_double (
		double * RESTRICT dest
		, const double * RESTRICT src
		, int len
	) {
		double src1 = src[ 0 ];
		int i = 0;
		for( ; i < len && (int&)src[i] & 31; ++i ) {
			dest[ i ] = src1;
			src1 = src[ i + 1 ];
		}
		double src2 = src[ i + 1 ];
		double src3 = src[ i + 2 ];
		double src4 = src[ i + 3 ];
		for( ; ( len - i ) >= 4; i += 4 ) {
			dest[ i ] = src1;
			dest[ i + 1 ] = src2;
			dest[ i + 2 ] = src3;
			dest[ i + 3 ] = src4;
			src1 = src[ i + 4 ];
			src2 = src[ i + 5 ];
			src3 = src[ i + 6 ];
			src4 = src[ i + 7 ];
		}
		if( len > i ) dest[ i ] = src1;
		if( len > i + 1 ) dest[ i + 1 ] = src2;
		if( len > i + 2 ) dest[ i + 2 ] = src3;
	}
}