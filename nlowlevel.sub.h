/* defines nlowlevel::sub functions

NOT validated

requires:
	//<ipp.h>
	//<mkl.h>
	//have called init_intel()

*/

#pragma once

namespace nlowlevel {
	void sub ( // a
		double *dest
		,const int len
		,const double *a
		,const double *b
	) {
		//vdSub(len, a, b, dest);
		for (int i = 0; i < len; ++i) {
			dest[i] = a[i] - b[i];
		}
	}

	void sub ( // s
		double *dest
		,const int len
		,const double *a
		,const double b
	) {
		//ippsSubC_64f(a, b, dest, len);
		for (int i = 0; i < len; ++i) {
			dest[i] = a[i] - b;
		}
	}

	void sub ( // s
		double *dest
		,const int len
		,const double a
		,const double *b
	) {
		//ippsSubCRev_64f(b, a, dest, len);
		for (int i = 0; i < len; ++i) {
			dest[i] = a - b[i];
		}
	}
}