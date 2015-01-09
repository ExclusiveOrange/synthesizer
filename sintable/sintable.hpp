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

todo:

	the limiting factor seems to be the apparently random memory
		accesses
	when several lookups are needed, it might be advantageous to
		perform the operation in three steps:

		1.	given a small array of "cycles", calculate and store
				(int index, int weight) pairs
		2.	given a small array of (index, weight) pairs,
				prefetch (diff, val) pairs, and calculate and store
				(diff, float weight, val) triplets
		3.	given a small array of (diff, weight, val) triplets,
				calculate and store val + diff * weight

	tuning the size of such arrays will be tricky, and efficiently dealing
		with triplets may necessitate aligning them either with a filler dword,
		or by keeping 'weight' in a separate list
		(though it may not be necessary to align them)

	the idea here is that if we keep the number of lookups fairly small,
		then the processor should be able to keep the results in L0 cache,
		so that by the time we calculate the final values, their components
		are ready and waiting

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

	__declspec( align( 64 ) )
	static struct element {
		elementtype diff;	// ( next.val - this.val ) / weightresolution
		elementtype val;	// sin( i * 2.0 * pi / tablesize )
	} table[ tablesize + 1 ];

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