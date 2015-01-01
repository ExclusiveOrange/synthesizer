/* defines global helper functions */

#pragma once

#include <math.h>
#include <windows.h>

#include "constants.h"
#include "ncircularbuffer.h"
#include "ninstruction.h"
#include "nrandom.h"

double mod1(double x) {
	return x - (int)x;
}

double modpi(double x) {
	const double rpi = 1.0 / M_PI;
	x *= rpi;
	return M_PI * (x - (int)x);
}
