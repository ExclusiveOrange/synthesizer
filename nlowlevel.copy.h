#pragma once

#include "restrict.h"

namespace nlowlevel {
	void
	fastcopy_double (
		double * RESTRICT dest
		, const double * RESTRICT src
		, int len
	) {
		double src0 = src[ 0 ];
		double src1 = src[ 1 ];
		double src2 = src[ 2 ];
		double src3 = src[ 3 ];
		int i = 0;
		// todo: change to i <= ( len - 4 )
		for( ; ( len - i ) >= 4; i += 4 ) {
			dest[ i ] = src0;
			dest[ i + 1 ] = src1;
			dest[ i + 2 ] = src2;
			dest[ i + 3 ] = src3;
			src0 = src[ i + 4 ];
			src1 = src[ i + 5 ];
			src2 = src[ i + 6 ];
			src3 = src[ i + 7 ];
		}
		if( len > i + 1 ) {
			dest[ i ] = src0;
			dest[ i + 1 ] = src1;
			if( len > i + 2 ) dest[ i + 2 ] = src2;
		} else if( len > i ) {
			dest[ i ] = src0;
		}
	}
}