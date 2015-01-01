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
		for (int i = 0; i < len; ++i) {
			srcdest[i] += a[i] * b[i];
		}
	}

	void addprod (
		double *srcdest
		,const int len
		,const double *a
		,const double b
	) {
		for (int i = 0; i < len; ++i) {
			srcdest[i] += a[i] * b;
		}
	}
}