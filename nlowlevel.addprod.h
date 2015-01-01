/* defines nlowlevel::addprod functions

validated

addprod *srcdest, len, *a, [b | *b]

srcdest[i] += a[i] * [b | b[i]

*/

#pragma once

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
		double src_plus_ab = srcdest[ 0 ] + a[ 0 ] * b;
		for(int i = 0; i < len; ++i) {
			srcdest[ i ] = src_plus_ab;
			src_plus_ab = srcdest[ i + 1 ] + a[ i + 1 ] * b;
		}
	}
}