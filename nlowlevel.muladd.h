/* defines nlowlevel::muladd functions

validated

muladd *srcdest, len, [mul | *mul], [add | *add]

srcdest[i] = srcdest[i] * [mul | mul[i]] + [add | add[i]]

*/

#pragma once

namespace nlowlevel {
	void muladd ( // a a
		double *srcdest
		,const int len
		,const double *mul
		,const double *add
	) {
		for (int i = 0; i < len; ++i) {
			srcdest[i] = srcdest[i] * mul[i] + add[i];
		}
	}

	void muladd ( // a s
		double *srcdest
		,const int len
		,const double *mul
		,const double add
	) {
		for (int i = 0; i < len; ++i) {
			srcdest[i] = srcdest[i] * mul[i] + add;
		}
	}

	void muladd ( // s a
		double *srcdest
		,const int len
		,const double mul
		,const double *add
	) {
		for (int i = 0; i < len; ++i) {
			srcdest[i] = srcdest[i] * mul + add[i];
		}
	}

	void muladd ( // s s
		double *srcdest
		,const int len
		,const double mul
		,const double add
	) {
		for (int i = 0; i < len; ++i) {
			srcdest[i] = srcdest[i] * mul + add;
		}
	}
}