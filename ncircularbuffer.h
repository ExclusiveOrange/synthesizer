/* defines ncircularbuffer functions */

#pragma once

#include "nlowlevel.copy.h"

namespace ncircularbuffer {
	void unwrap (
		double *dest_linear
		,const double *src_circular
		,const int size
		,const int start
	) {
		//memcpy(dest_linear + (size - start), src_circular, sizeof(double) * start);
		//memcpy(dest_linear, src_circular + start, sizeof(double) * (size - start));
		nlowlevel::copy( dest_linear + ( size - start ), src_circular, start );
		nlowlevel::copy( dest_linear, src_circular + start, ( size - start ) );
	}

	// returns new start
	int unwrap_partial (
		double *dest_linear
		,const double *src_circular
		,const int size
		,const int start
		,const int len
	) {
		if (start <= size - len) {
			//memcpy(dest_linear, src_circular + start, sizeof(double) * len);
			nlowlevel::copy( dest_linear, src_circular + start, len );
			if (start + len == size) return 0;
			return start + len;
		} else {
			//memcpy(dest_linear + (size - start), src_circular, sizeof(double) * (len - (size - start)));
			//memcpy(dest_linear, src_circular + start, sizeof(double) * (size - start));
			nlowlevel::copy( dest_linear + ( size - start ), src_circular, ( len - ( size - start ) ));
			nlowlevel::copy( dest_linear, src_circular + start, ( size - start ) );
			return len - (size - start);
		}
	}

	void wrap (
		double *dest_circular
		, const double *src_linear
		,const int size
		,const int start
	) {
		//memcpy(dest_circular + start, src_linear, sizeof(double) * (size - start));
		//memcpy(dest_circular, src_linear + (size - start), sizeof(double) * start);
		nlowlevel::copy( dest_circular + start, src_linear, ( size - start ) );
		nlowlevel::copy( dest_circular, src_linear + ( size - start ), start );
	}

	// returns new start
	int wrap_partial (
		double * __restrict dest_circular
		, const double * __restrict src_linear
		,const int size
		,const int start
		,const int len
	) {
		if (start <= size - len) {
			//memcpy(dest_circular + start, src_linear, sizeof(double) * len);
			nlowlevel::copy( dest_circular + start, src_linear, len );
			if (start + len == size) return 0;
			return start + len;
		} else {
			//memcpy(dest_circular + start, src_linear, sizeof(double) * (size - start));
			//memcpy(dest_circular, src_linear + (size - start), sizeof(double) * (len - (size - start)));
			nlowlevel::copy( dest_circular + start, src_linear, ( size - start ) );
			nlowlevel::copy( dest_circular, src_linear + ( size - start ), ( len - ( size - start ) ) );
			return len - (size - start);
		}
	}

}