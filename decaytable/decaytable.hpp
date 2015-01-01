/* approximation of exponential decay
	by Atlee Brink
	version 2014.12.31

todo:

	test whether it is faster in practice to define the table statically
	(I suspect it won't make any difference)

reference:

	namespace decaytable

	void init ( void )
		call once before using lookup(...)

	double lookup ( double zero_to_one )
		returns an approximation of
			exp( -8 * zero_to_one ) - ( zero_to_one * exp( -8 ) )
			which is in the range of [1, 0]
		zero_to_one must be in [0, 1]
			undefined behavior otherwise

notes:

	decay_rate is somewhat arbitrary: 1 is a straight line, while 8 or 9 is respectable
	tablebits + weightbits <= 31 for optimal results,
		if tablebits + weightbits >= 32, something seems to overflow somewhere
	if decay_rate is larger, tablebits become more important than weightbits,
		though the values I've chosen (tablebits = 9, weightbits = 22), seems to
		yield good results with regard to memory usage and audio quality

*/

#pragma once

#include <cmath>
#include <cstdint>

namespace decaytable {
	const auto decay_rate = 8;

	const auto tablebits = 9;
	const auto tablesize = 1 << tablebits;
	const auto weightbits = 22;
	const auto weightresolution = 1 << weightbits;
	const auto resolution = weightresolution << tablebits;

	const auto resolution_mask = resolution - 1;
	const auto weightresolution_r = 1.0 / weightresolution;
	const auto weightresolution_mask = weightresolution - 1;

	typedef float elementtype;

	const auto table_extra = 16;

	static struct element {
		elementtype val;
		elementtype diff;
	} table[ tablesize + table_extra ];

	void
	init (
		void
	) {
		const auto step = 1.0 / ( tablesize - 1 );

		table[ 0 ].val = 1.0;
		for( auto i = 1; i < tablesize; ++i ) {
			auto x = i * step;
			table[ i ].val = exp( -decay_rate * x ) - ( x * exp( -decay_rate ) );
			table[ i - 1 ].diff = ( table[ i ].val - table[ i - 1 ].val ) * weightresolution_r;
		}
		table[ tablesize - 1 ].diff = ( -table[ tablesize - 1 ].val ) * weightresolution_r;
		for( auto k = 0; k < table_extra; ++k ) {
			table[ tablesize + k ].val = 0.0;
			table[ tablesize + k ].diff = 0.0;
		}
	}

	double
	lookup(
		double zero_to_one
	) {
		auto composite = (int64_t)( zero_to_one * resolution_mask );
		auto index = composite >> weightbits;
		auto weight = composite & weightresolution_mask;

		return table[ index ].val + ( table[ index ].diff * weight );
	}
}