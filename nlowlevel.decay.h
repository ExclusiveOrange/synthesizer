/* defines nlowlevel::decay functions */

#pragma once

#include "decaytable/decaytable.hpp" // magic

namespace nlowlevel {
	void
	init_decay (
		void
	) {
		decaytable::init();
	}

	void decay (
		double *dest
		,const int len
		,const double start
		,const double end
	) {
		double slope = (end - start) / len;
		double id = start;
		for (int i = 0; i < len; ++i) {
			dest[i] = decaytable::lookup(id);
			id += slope;
		}
	}
}