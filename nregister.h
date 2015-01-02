/* defines namespace nregister

usage:
	Must call init() once per thread.

*/

#pragma once

namespace nregister {
	const int len = 1024;
	const int num = 8;

	double rate;
	double rrate;
	double duration;

	// we allocate one extra register so that sloppy-fast memory reads can read past r7 without breaking
	__declspec(thread) __declspec(align(64)) double localreg[num + 1][len];

	void zero0 () {
		for(int i = 0; i < nregister::len; i += 4) {
			nregister::localreg[ 0 ][ i ] = 0.0;
			nregister::localreg[ 0 ][ i + 1 ] = 0.0;
			nregister::localreg[ 0 ][ i + 2 ] = 0.0;
			nregister::localreg[ 0 ][ i + 3 ] = 0.0;
		}
	}
}