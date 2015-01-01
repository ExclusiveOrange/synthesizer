/* defines helper functions for namespace nclip */

#pragma once

namespace nclip {
	double mod1(double x) {
		return x - (int)x;
	}

	int tto ( // time to offset conversion
		const double time
	) {
		return (int)(time * nregister::rate);
	}
}