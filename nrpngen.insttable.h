/* defines nrpngen instruction table */

#pragma once

namespace nrpngen {
	char *instnames[] = {
		"noop", "fill", "add", "sub", "mul", "addprod", "sine", "triangle",
		"square", "sawfore", "sawback", "line", "muladd", "noise", "exp",
		"decay", "delay", /*"lowpass", "highpass",*/ 0
	};

	struct sinst {
		char opcodebase;
		char numparams;
		char numversions;
		bool isreg[4][4];
	} INSTS[] = {
		{0x00, 0, 1} // noop
		,{0x01, 2, 1, {{1, 0}}} // fill
		,{0x02, 3, 2, {{1, 1, 1}, {1, 1, 0}}} // add
		,{0x04, 3, 3, {{1, 1, 1}, {1, 1, 0}, {1, 0, 1}}} // sub
		,{0x07, 3, 2, {{1, 1, 1}, {1, 1, 0}}} // mul
		,{0x09, 3, 2, {{1, 1, 1}, {1, 1, 0}}} // addprod
		,{0x0b, 4, 4, {{1, 0, 1, 1}, {1, 0, 1, 0}, {1, 0, 0, 1}, {1, 0, 0, 0}}} // sine
		,{0x0f, 4, 4, {{1, 0, 1, 1}, {1, 0, 1, 0}, {1, 0, 0, 1}, {1, 0, 0, 0}}} // triangle
		,{0x13, 4, 4, {{1, 0, 1, 1}, {1, 0, 1, 0}, {1, 0, 0, 1}, {1, 0, 0, 0}}} // square
		,{0x17, 4, 4, {{1, 0, 1, 1}, {1, 0, 1, 0}, {1, 0, 0, 1}, {1, 0, 0, 0}}} // sawfore
		,{0x1b, 4, 4, {{1, 0, 1, 1}, {1, 0, 1, 0}, {1, 0, 0, 1}, {1, 0, 0, 0}}} // sawback
		,{0x1f, 3, 1, {{1, 0, 0}}} // line
		,{0x20, 3, 4, {{1, 1, 1}, {1, 1, 0}, {1, 0, 1}, {1, 0, 0}}} // muladd
		,{0x24, 3, 1, {{1, 0, 0}}} // noise
		,{0x25, 2, 1, {{1, 1}}} // exp
		,{0x26, 1, 1, {{1}}} // decay
		,{0xf0, 1, 1, {{0}}} // delay
		//,{0xf1, 1, 1, {{0}}} // lowpass
		//,{0xf2, 1, 1, {{0}}} // highpass
	};
}