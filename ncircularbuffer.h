/* defines ncircularbuffer functions */

#pragma once

namespace ncircularbuffer {
	void unwrap (
		double *dest_linear
		,const double *src_circular
		,const int size
		,const int start
	) {
		memcpy(dest_linear + (size - start), src_circular, sizeof(double) * start);
		memcpy(dest_linear, src_circular + start, sizeof(double) * (size - start));
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
			memcpy(dest_linear, src_circular + start, sizeof(double) * len);
			if (start + len == size) return 0;
			return start + len;
		} else {
			memcpy(dest_linear + (size - start), src_circular, sizeof(double) * (len - (size - start)));
			memcpy(dest_linear, src_circular + start, sizeof(double) * (size - start));
			return len - (size - start);
		}
	}

	void wrap (
		double *dest_circular
		,const double *src_linear
		,const int size
		,const int start
	) {
		memcpy(dest_circular + start, src_linear, sizeof(double) * (size - start));
		memcpy(dest_circular, src_linear + (size - start), sizeof(double) * start);
	}

	// returns new start
	int wrap_partial (
		double *dest_circular
		,const double *src_linear
		,const int size
		,const int start
		,const int len
	) {
		if (start <= size - len) {
			memcpy(dest_circular + start, src_linear, sizeof(double) * len);
			if (start + len == size) return 0;
			return start + len;
		} else {
			memcpy(dest_circular + start, src_linear, sizeof(double) * (size - start));
			memcpy(dest_circular, src_linear + (size - start), sizeof(double) * (len - (size - start)));
			return len - (size - start);
		}
	}

}