/* defines nclip::noise functions

validated

*/

#pragma once

namespace nclip {
	void noise (
		const double start
		,const ninstruction::sinst &inst
	) {
		nlowlevel::noise (
			nregister::localreg[inst.reg0] + tto(inst.start - start)
			,tto(inst.len)
			,inst.scalar_a
			,inst.scalar_b
		);
	}

	void bnoise (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::noise (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,inst.scalar_a
			,inst.scalar_b
		);
	}

	void enoise (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::noise (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,inst.scalar_a
			,inst.scalar_b
		);
	}

	void benoise (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::noise (
			nregister::localreg[inst.reg0]
			,nregister::len
			,inst.scalar_a
			,inst.scalar_b
		);
	}
}