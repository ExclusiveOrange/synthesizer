/* defines nlowlevel::mul functions

validated

requires:
	<ipp.h>
	have called init_intel()

*/

#pragma once

namespace nlowlevel {
	void mul (
		double *dest
		,const int len
		,const double *a
		,const double *b
	) {
		//double ab = a[ 0 ] * b[ 0 ];
		//for(int i = 0; i < len; ++i) {
		//	dest[ i ] = ab;
		//	ab = a[ i + 1 ] * b[ i + 1 ];
		//}
		double a0 = a[ 0 ];
		double b0 = b[ 0 ];
		for( int i = 0; i < len; ++i ) {
			dest[ i ] = a0 * b0;
			a0 = a[ i + 1 ];
			b0 = b[ i + 1 ];
		}
	}

	void mul (
		double *dest
		,const int len
		,const double *a
		,const double b
	) {
		double ab = a[ 0 ] * b;
		for(int i = 0; i < len; ++i) {
			dest[ i ] = ab;
			ab = a[ i + 1 ] * b;
		}
	}
}