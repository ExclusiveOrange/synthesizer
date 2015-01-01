/* defines nclip::exp functions

validated

*/

#pragma once

namespace nclip {
	void exp (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		nlowlevel::exp (
			nregister::localreg[inst.reg0] + offset
			,tto(inst.len)
			,nregister::localreg[inst.reg1] + offset
		);
	}

	void bexp (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::exp (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,nregister::localreg[inst.reg1]
		);
	}

	void eexp (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::exp (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,nregister::localreg[inst.reg1] + offset
		);			
	}

	void beexp (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::exp (
			nregister::localreg[inst.reg0]
			,nregister::len
			,nregister::localreg[inst.reg1]
		);
	}
}