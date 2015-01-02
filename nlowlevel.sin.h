/* defines nlowlevel::sin functions

seems to work!

description:
	sin (
		double *dest                  // destination array
		,const int len                // length of dest
		,const double rrate           // 1.0 / samples_per_second
		,const double mag             // magnitude of result
		,const double freq | *freq    // scalar or array of frequency values, in hertz
		,[double &phase |             // starting phase value, reuse next time
			[const double *phase        // array of phase values
			,double &acc]]              // set to 0.0 to start, reuse next time
	);

*/

#pragma once

#include "constants.h"
#include "sintable/sintable.hpp" // magic

#include <math.h>

// assign one of these...
#define FASTSINEFUNC( X ) ( nlowlevel::sine1fast( X ) ) // parabolic approximation (faster than the standard library but audibly inaccurate)
#define TABLESINEFUNC( X ) ( sintable::lookup( X ) ) // linearly interpolated table lookup (fastest if there is good caching, also accurate)
#define STANDARDSINEFUNC( X ) ( ::sin( X * M_2PI ) ) // standard math library (slowest)
// .. to this SINEFUNC( X ) macro.
#define SINEFUNC( X ) ( TABLESINEFUNC(X) )

namespace nlowlevel {
	namespace {
		double sine1fast(double x) { // there might be a way to make this faster, but the compiler already does well here
			x = (x - floor(x)) * 2.0 - 1.0; // wrap to [-1..1]
			x *= -4.0 * (1.0 - abs(x));
			const double P = 0.218; // 0.225, 0.218
			const double Q = 0.792; // 0.775, 0.782
			//return x * (P * (abs(x) - 1.0) + 1.0); // low precision
			return x * (Q + P * abs(x)); // high precision
		}

		double sine(double x) {
			return SINEFUNC(x);
		}
	}

	void
	init_sin (
		void
	) {
		sintable::init();
	}

	void sin ( // a a
		double *dest
		,const int len
		,const double rrate
		,const double mag
		,const double *freq
		,const double *phase
		,double &acc
	) {
		double freq1 = freq[ 0 ];
		double phase1 = phase[ 0 ];
		for (int i = 0; i < len; ++i) {
			acc += freq1 * rrate;
			freq1 = freq[ i + 1 ];
			dest[i] = mag * sine(phase1 + acc);
			phase1 = phase[ i + 1 ];
		}
	}

	void sin ( // a s
		double *dest
		,const int len
		,const double rrate
		,const double mag
		,const double *freq
		,double &phase
	) {	
		double freq1 = freq[ 0 ];
		double freq2 = freq[ 1 ];
		double phase1 = phase + freq1 * rrate;
		int i = 0;
		for( ; i < len; ++i ) {
			dest[ i ] = mag * sine( phase1 );
			freq1 = freq2 * rrate;
			freq2 = freq[ i + 2 ];
			phase1 += freq1;
		}
		phase = phase1 - freq1;
	}

	void sin ( // s a
		double *dest
		,const int len
		,const double rrate
		,const double mag
		,const double freq
		,const double *phase
		,double &acc
	) {
		double phase1 = phase[ 0 ];
		for (int i = 0; i < len; ++i) {
			acc += freq * rrate;
			dest[i] = mag * sine(phase1 + acc);
			phase1 = phase[ i + 1 ];
		}
	}

	void sin ( // s s
		double *dest
		,const int len
		,const double rrate
		,const double mag
		,const double freq
		,double &phase
	) {
		double phase1 = phase + freq * rrate;
		for (int i = 0; i < len; ++i) {
			dest[i] = mag * sine(phase1);
			phase1 += freq * rrate;
		}
		phase = phase1 - freq * rrate;
	}
}