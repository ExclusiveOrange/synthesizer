#pragma once

namespace nlowlevel {
	void
	copy (
		double * __restrict dest
		,const double * __restrict src
		,int len
	) {
		double d = src[ 0 ];
		for( int i = 0; i < len; ++i ) {
			dest[ i ] = d;
			d = src[ i + 1 ];
		}
	}
}