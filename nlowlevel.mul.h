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
		for (int i = 0; i < len; ++i) {
			dest[i] = a[i] * b[i];
		}
	}

	void mul (
		double *dest
		,const int len
		,const double *a
		,const double b
	) {
		for (int i = 0; i < len; ++i) {
			dest[i] = a[i] * b;
		}
	}
}