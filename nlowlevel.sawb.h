/* defines nlowlevel::sawb functions

validated

*/

#pragma once

#include "constants.h"

namespace nlowlevel {
	namespace {
		double sawb(double x, const double rrate) {
			x += 0.5;
			return 1.0 - (2.0 + rrate * 2.0) * (x - (int)x);
		}
	}

	void sawb ( // a a
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
			dest[i] = mag * sawb(phase[i] + acc, rrate);
		}
	}

	void sawb ( // a s
		double *dest
		,const int len
		,const double rrate
		,const double mag
		,const double *freq
		,double &phase
	) {
		for (int i = 0; i < len; ++i) {
			dest[i] = mag * sawb((phase += freq[i] * rrate), rrate);
		}
	}

	void sawb ( // s a
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
			dest[i] = mag * sawb(phase[i] + acc, rrate);
		}
	}

	void sawb ( // s s
		double *dest
		,const int len
		,const double rrate
		,const double mag
		,const double freq
		,double &phase
	) {
		for (int i = 0; i < len; ++i) {
			dest[i] = mag * sawb((phase += freq * rrate), rrate);
		}
		//if (mag != 0.0) {
		//	double p = mod1(phase + 0.5) * M_2PI;
		//	ippsTriangle_Direct_64f(dest, len, mag, freq * rrate, M_LTPI, &p);
		//	phase = mod1(p / M_2PI + 0.5);
		//} else {
		//	for (int i = 0; i < len; ++i) {
		//		dest[i] = 0.0;
		//	}
		//}
	}
}