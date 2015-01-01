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
		for (int i = 0; i < len; ++i) {
			dest[i] = a[i] + b[i];
		}
	}

	void add ( // s
		double *dest
		,const int len
		,const double *a
		,const double b
	) {
		for (int i = 0; i < len; ++i) {
			dest[i] = a[i] + b;
		}
	}
}