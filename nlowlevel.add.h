/* defines nlowlevel::add functions

validated

requires:
	<ipp.h>
	<mkl.h>
	have called init_intel()

*/

#pragma once

namespace nlowlevel {
	void add ( // a
		double *dest
		,const int len
		,const double *a
		,const double *b
	) {
		double a_plus_b = a[ 0 ] + b[ 0 ];
		for (int i = 0; i < len; ++i) {
			dest[ i ] = a_plus_b;
			a_plus_b = a[ i + 1 ] + b[ i + 1 ];
		}
	}

	void add ( // s
		double *dest
		,const int len
		,const double *a
		,const double b
	) {
		double a_plus_b = a[ 0 ] + b;
		for (int i = 0; i < len; ++i) {
			dest[ i ] = a_plus_b;
			a_plus_b = a[ i + 1 ] + b;
		}
	}
}