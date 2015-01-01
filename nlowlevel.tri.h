/* defines nlowlevel::tri functions

NOT validated

*/

#pragma once

#include "constants.h"

namespace nlowlevel {
	namespace {
		double tri(double x) {
			x += 0.25;
			double phase = 4.0 * (x - (int)x);
			double s = (double)(int)(phase * 0.5);
			double a = (phase - 1.0) * (1.0 - s);
			double b = (3.0 - phase) * s;
			return a + b;
		}
	}

	void tri ( // a a
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
			dest[i] = mag * tri(phase[i] + acc);
		}
	}

	void tri ( // a s
		double *dest
		,const int len
		,const double rrate
		,const double mag
		,const double *freq
		,double &phase
	) {
		for (int i = 0; i < len; ++i) {
			dest[i] = mag * tri((phase += freq[i] * rrate));
		}
	}

	void tri ( // s a
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
			dest[i] = mag * tri(phase[i] + acc);
		}
	}

	void tri ( // s s
		double *dest
		,const int len
		,const double rrate
		,const double mag
		,const double freq
		,double &phase
	) {
		//if (mag != 0.0) {
		//	double p = mod1(phase + 0.75) * M_2PI;
		//	ippsTriangle_Direct_64f(dest, len, mag, freq * rrate, 0.0, &p);
		//	phase = mod1(p / M_2PI + 0.25);
		//} else {
		//	for (int i = 0; i < len; ++i) {
		//		dest[i] = 0.0;
		//	}
		//}
		for (int i = 0; i < len; ++i) {
			dest[i] = mag * tri((phase += freq * rrate));
		}
	}
}