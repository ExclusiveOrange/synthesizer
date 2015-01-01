/* defines nclip::line functions

validated

*/

#pragma once

namespace nclip {
	void line (
		const double start
		,const ninstruction::sinst &inst
	) {
		nlowlevel::line (
			nregister::localreg[inst.reg0] + tto(inst.start - start)
			,tto(inst.len)
			,inst.scalar_a
			,(inst.scalar_b - inst.scalar_a) / inst.len * nregister::rrate
		);
	}

	void bline (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::line (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,inst.scalar_a + (inst.scalar_b - inst.scalar_a) * ((start - inst.start) / inst.len)
			,(inst.scalar_b - inst.scalar_a) / inst.len * nregister::rrate
		);
	}

	void eline (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::line (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,inst.scalar_a
			,(inst.scalar_b - inst.scalar_a) / inst.len * nregister::rrate
		);
	}

	void beline (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::line (
			nregister::localreg[inst.reg0]
			,nregister::len
			,inst.scalar_a + (inst.scalar_b - inst.scalar_a) * ((start - inst.start) / inst.len)
			,(inst.scalar_b - inst.scalar_a) / inst.len * nregister::rrate
		);
	}
}