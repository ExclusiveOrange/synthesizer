/* defines namespace nclip */

#pragma once

#include "nlowlevel.h"
#include "nregister.h"

namespace nclip {
	struct uacc {
		double d;
		int i;
	};
}

#include "nclip.dispatch.h"

namespace nclip {
	void clip (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		if (inst.start + inst.len <= start) return;
		if (inst.start > start + nregister::duration) return;
		if (inst.start < start) {
			if (inst.start + inst.len < start + nregister::duration) {
				fbclip[inst.opcode](start, inst, acc);
			} else {
				fclip[inst.opcode](start, inst, acc);
			}
		} else if (inst.start + inst.len <= start + nregister::duration) {
			fnoclip[inst.opcode](start, inst);
		} else {
			feclip[inst.opcode](start, inst, acc);
		}
	}
}