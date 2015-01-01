/* defines namespace ninstruction */

#pragma once

#include <stdio.h>

namespace ninstruction {
	struct sinst {
		float start;
		float len;
		unsigned char opcode;
		unsigned char reg0;
		unsigned char reg1;
		unsigned char reg2;
		float scalar_a;
		float scalar_b;
		float scalar_c;
	};

	void readinst(sinst &inst) {
		printf(
			"sinst {\n"
			" start = %f\n"
			" len = %f\n"
			" opcode = 0x%02x\n"
			" reg0 = %u\n"
			" reg1 = %u\n"
			" reg2 = %u\n"
			" scalar_a = %f\n"
			" scalar_b = %f\n"
			" scalar_c = %f\n"
			"}\n"
			,inst.start
			,inst.len
			,inst.opcode
			,inst.reg0
			,inst.reg1
			,inst.reg2
			,inst.scalar_a
			,inst.scalar_b
			,inst.scalar_c
		);
	}
}