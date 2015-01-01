/* defines nlowlevel::sqr functions

validated

*/

#pragma once

#include "constants.h"

namespace nlowlevel {
	namespace {
		double sqr(double x) {
			x += 0.5;
			return (double)((((int)(x * 2.0) & 1) << 1) - 1);
		}
	}

	void sqr ( // a a
		double *dest
		,const int len
		,const double rrate
		,const double mag
		,const double *freq
		,const double *phase
		,double &acc
	) {
		for (int i = 0; i < len; ++i) {
			acc += freq[i] * rrate;
			dest[i] = mag * sqr(phase[i] + acc);
		}
	}

	void sqr ( // a s
		double *dest
		,const int len
		,const double rrate
		,const double mag
		,const double *freq
		,double &phase
	) {
		for (int i = 0; i < len; ++i) {
			dest[i] = mag * sqr((phase += freq[i] * rrate));
		}
	}

	void sqr ( // s a
		double *dest
		,const int len
		,const double rrate
		,const double mag
		,const double freq
		,const double *phase
		,double &acc
	) {
		for (int i = 0; i < len; ++i) {
			acc += freq * rrate;
			dest[i] = mag * sqr(phase[i] + acc);
		}
	}

	void sqr ( // s s
		double *dest
		,const int len
		,const double rrate
		,const double mag
		,const double freq
		,double &phase
	) {
		for (int i = 0; i < len; ++i) {
			dest[i] = mag * sqr((phase += freq * rrate));
		}
	}
}