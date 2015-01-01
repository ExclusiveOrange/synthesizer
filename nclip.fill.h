/* defines nclip::fill functions

validated

*/

#pragma once

namespace nclip {
	void fill (
		const double start
		,const ninstruction::sinst &inst
	) {
		nlowlevel::fill (
			nregister::localreg[inst.reg0] + tto(inst.start - start)
			,tto(inst.len)
			,inst.scalar_a
		);
	}

	void bfill (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::fill (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,inst.scalar_a
		);
	}

	void efill (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::fill (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,inst.scalar_a
		);
	}

	void befill (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::fill (
			nregister::localreg[inst.reg0]
			,nregister::len
			,inst.scalar_a
		);
	}
}