/* defines namespace nrandom

Room for improvement:

	Find a faster way to approximate the Gaussian distribution.
	It doesn't need to be exact, just approximate and smooth.

validated

requires:
	/dSFMT 2.2.1/dSFMT.h et al.
	/dSFMT 2.2.1/dSFMT.c must be compiled with DSFMT_MEXP=521;HAVE_SSE2
	<intrin.h>
	<math.h>

usage:
	Must call nrandom::init() once per thread.

*/

#pragma once

#include "dSFMT-src-2.2.1/dSFMT.h"

#include <intrin.h>
#include <math.h>

namespace nrandom {
	__declspec(thread) dsfmt_t dsfmt;
	__declspec(thread) double u, v, m, spare;
	__declspec(thread) bool bspare;

	void init() {
		__int64 time;
		time = __rdtsc();
		dsfmt_init_gen_rand(&dsfmt, (uint32_t)(time & 0xffffffff));
		bspare = false;
	}

	void _genpolar() { // Marsaglia polar method
		double s;
		do {
			u = 2.0 * (dsfmt_genrand_close1_open2(&dsfmt) - 1.5);
			v = 2.0 * (dsfmt_genrand_close1_open2(&dsfmt) - 1.5);
			s = u*u + v*v;
		} while (s >= 1.0 || s == 0.0);
		m = sqrt(-2.0 * log(s) / s);
	}

	double gaussian (
		const double mu
		,const double sigma
	) {
		if (bspare) {
			bspare = false;
			return mu + spare * sigma;
		}
		_genpolar();
		spare = v * m;
		bspare = true;
		return mu + u * m * sigma;
	}

	void gaussian (
		double *dest
		,const unsigned int len
		,const double mu
		,const double sigma
	) {
		unsigned int i = 0;
		for (; i < (len / 2); i += 2) {
			_genpolar();
			dest[i] = mu + u * m * sigma;
			dest[i + 1] = mu + v * m * sigma;
		}
		for (; i < len; i++) {
			dest[i] = gaussian(mu, sigma);
		}
	}

	void uniform (
		double *dest
		,const unsigned int len
		,const double a
		,const double b
	) {
		const double c = b - a;
		unsigned int i = 0;
		if (len >= DSFMT_N64) {
			if ((unsigned __int64)dest & 15) {
				dest[i++] = a + c * dsfmt_genrand_close_open(&dsfmt);
			}
			unsigned int block = (len - i) & 0xfffffffe;
			dsfmt_fill_array_close_open(&dsfmt, dest + i, block);
			for (; i < block; i++) {
				dest[i] = a + c * dest[i];
			}
		}
		for (; i < len; i++) {
			dest[i] = a + c * dsfmt_genrand_close_open(&dsfmt);
		}
	}

	double uniform (
		const double a
		,const double b
	) {
		return a + (b - a) * dsfmt_genrand_close_open(&dsfmt);
	}
}