/* defines nlowlevel::addprod functions

validated

addprod *srcdest, len, *a, [b | *b]

srcdest[i] += a[i] * [b | b[i]

*/

#pragma once

#include "restrict.h"

namespace nlowlevel {
	void addprod (
		double *srcdest
		,const int len
		,const double *a
		,const double *b
	) {
		double src_plus_ab = srcdest[ 0 ] + a[ 0 ] * b[ 0 ];
		for(int i = 0; i < len; ++i) {
			srcdest[ i ] = src_plus_ab;
			src_plus_ab = srcdest[ i + 1 ] + a[ i + 1 ] * b[ i + 1 ];
		}
	}

	void addprod (
		double *srcdest
		,const int len
		,const double *a
		,const double b
	) {
		if( len < 1 ) return;
		double a0 = a[ 0 ];
		double src0 = srcdest[ 0 ];
		int i = 0;
		for( ; i < len - 1; ++i ) {
			double ab = a0 * b;
			a0 = a[ i + 1 ];
			srcdest[ i ] = src0 + ab;
			src0 = srcdest[ i + 1 ];
		}
		srcdest[ i ] = src0 + a0 * b;
	}
}