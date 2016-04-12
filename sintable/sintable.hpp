/* approximation of sine function using two interleaven tables
	by Atlee Brink
	version 2016.04.08

reference:

	namespace sintable
	
	void init ( void )
		call once before using lookup(...)
	
	double lookup ( double cycles )
		returns an approximation of sin( cycles * pi * 2 )

notes:

	seems to be much faster than sin()
	seems to yield about 4-5 significant decimal digits
	sequential outputs should be smooth

	tuned to give good results for cycles < 2^33;
		beyond that, precision will begin to degrade
		( 52 - ( 9 + 10 ) = 33 bits )
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
	const auto table_mask = tablesize - 1;

	typedef float elementtype;
	typedef double element_container;

	static union element {
		struct {
			elementtype diff;	// ( next.val - this.val ) / weightresolution
			elementtype val;	// sin( i * 2.0 * pi / tablesize )
		};
		element_container container;
	} table[ tablesize ];

	const auto pi = 3.141592653589793;
	
	void
	init (
		void
	) {
		const auto step = pi * 2.0 / tablesize;

		table[0].val = 0.0;
		for (auto i = 1; i < tablesize; ++i) {
			table[i].val = (elementtype)sin( i * step );
			table[ i - 1 ].diff = (elementtype)( ( sin( i * step ) - sin( ( i - 1 ) * step ) ) * weightresolution_r );
		}
		table[ tablesize - 1 ].diff = table[ 0 ].diff;
	}

	double
	lookup (
		double cycles
	) {
		static const element *table = sintable::table;

		auto composite = (int64_t)( cycles * resolution );
		auto index = ( composite & resolution_mask ) >> weightbits;
		auto weight = composite & weightresolution_mask;

		return ( table[ index ].diff * weight ) + table[ index ].val;
	}
}