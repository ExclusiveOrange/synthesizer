/* defines ncircularbuffer functions */

#pragma once

#include "nlowlevel.copy.h"
#include "restrict.h"

namespace ncircularbuffer {
	void unwrap (
		double * RESTRICT dest_linear
		, const double * RESTRICT src_circular
		,const int size
		,const int start
	) {
		nlowlevel::fastcopy_double( dest_linear + ( size - start ), src_circular, start );
		nlowlevel::fastcopy_double( dest_linear, src_circular + start, ( size - start ) );
	}

	// returns new start
	int unwrap_partial (
		double * RESTRICT dest_linear
		,const double * RESTRICT src_circular
		,const int size
		,const int start
		,const int len
	) {
		if (start <= size - len) {
			nlowlevel::fastcopy_double( dest_linear, src_circular + start, len );
			if (start + len == size) return 0;
			return start + len;
		} else {
			nlowlevel::fastcopy_double( dest_linear + ( size - start ), src_circular, ( len - ( size - start ) ));
			nlowlevel::fastcopy_double( dest_linear, src_circular + start, ( size - start ) );
			return len - (size - start);
		}
	}

	void wrap (
		double * RESTRICT dest_circular
		, const double * RESTRICT src_linear
		,const int size
		,const int start
	) {
		nlowlevel::fastcopy_double( dest_circular + start, src_linear, ( size - start ) );
		nlowlevel::fastcopy_double( dest_circular, src_linear + ( size - start ), start );
	}

	// returns new start
	int wrap_partial (
		double * RESTRICT dest_circular
		, const double * RESTRICT src_linear
		,const int size
		,const int start
		,const int len
	) {
		if (start <= size - len) {
			nlowlevel::fastcopy_double( dest_circular + start, src_linear, len );
			if (start + len == size) return 0;
			return start + len;
		} else {
			nlowlevel::fastcopy_double( dest_circular + start, src_linear, ( size - start ) );
			nlowlevel::fastcopy_double( dest_circular, src_linear + ( size - start ), ( len - ( size - start ) ) );
			return len - (size - start);
		}
	}

}