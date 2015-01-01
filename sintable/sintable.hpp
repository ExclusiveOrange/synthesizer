/* approximation of sine function using two interleaven tables
	by Atlee Brink
	version 2014.12.30

reference:

	namespace sintable
	
	void init ( void )
		call once before using lookup(...)
	
	double lookup ( double cycles )
		returns an approximation of sin( cycles * pi * 2 )
		cycles must be >= 0.0
		undefined behavior when cycles < 0.0

notes:

	seems to be much faster than sin()
	seems to yield about 4-5 significant decimal digits
	sequential outputs should be smooth

	tuned to give good results for cycles < 2^33;
		beyond that, precision will begin to degrade

*/

#pragma once

#include <cfloat>
#include <cmath>
#include <cstdint>

namespace sintable {
	const auto tablebits = 9;
	const auto tablesize = 1 << tablebits;
	const auto weightbits = 10;
	const auto weightresolution = 1 << weightbits;
	const auto resolution = weightresolution << tablebits;
	
	// these are to help stupid compilers with optimisation
	const auto weightresolution_r = 1.0 / weightresolution;
	const auto weightresolution_mask = weightresolution - 1;
	const auto resolution_mask = resolution - 1;

	typedef float elementtype;

	__declspec( align( 32 ) )
	static struct element {
		elementtype diff;	// ( next.val - this.val ) / weightresolution
		elementtype val;	// sin( i * 2.0 * pi / tablesize )
	} table[ tablesize ];

	const auto pi = 3.141592653589793;
	
	void
	init (
		void
	) {
		const auto step = pi * 2.0 / tablesize;

		table[0].val = 0.0;
		for (auto i = 1; i < tablesize; ++i) {
			table[i].val = sin( i * step );
			table[ i - 1 ].diff = ( table[i].val - table[ i - 1 ].val ) * weightresolution_r;
		}
		table[ tablesize - 1 ].diff = ( -table[ tablesize - 1 ].val ) * weightresolution_r;
	}
	
	double
	lookup (
		double cycles
	) {
		auto composite = (int64_t)( cycles * resolution ) & resolution_mask;
		auto index = composite >> weightbits;
		auto weight = composite & weightresolution_mask;

		return table[index].val + ( table[index].diff * weight );
	}
}