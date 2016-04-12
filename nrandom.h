/* defines namespace nrandom

2016.04.08:
	Now that C++11 is a thing (it wasn't when I first wrote this file),
	we have standardized (and fast) random number generators built-in.
	Today's rewrite eliminates dependencies on dSFMT.h and dSFMT.c.

*/

#pragma once

#include <random>

namespace nrandom {
	std::random_device randev;
	std::mt19937_64 rangen( randev() );

	double exponential (
		double mean
	) {
		static std::exponential_distribution<> expdist;
		return expdist( rangen ) * mean;
	}

	double gaussian (
		double mean,
		double stddev
	) {
		static std::normal_distribution<> normdist;
		return normdist( rangen ) * stddev + mean;
	}

	double uniform (
		double a,
		double b
	) {
		static std::uniform_real_distribution<> unidist;
		return unidist( rangen ) * ( b - a ) + a;
	}
}