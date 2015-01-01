/* defines nclip::mul functions

validated

*/

#pragma once

namespace nclip {
	void mul_a (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		nlowlevel::mul (
			nregister::localreg[inst.reg0] + offset
			,tto(inst.len)
			,nregister::localreg[inst.reg1] + offset
			,nregister::localreg[inst.reg2] + offset
		);
	}

	void mul_s (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		nlowlevel::mul (
			nregister::localreg[inst.reg0] + offset
			,tto(inst.len)
			,nregister::localreg[inst.reg1] + offset
			,inst.scalar_a
		);
	}

	void bmul_a (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::mul (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,nregister::localreg[inst.reg1]
			,nregister::localreg[inst.reg2]
		);
	}

	void bmul_s (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::mul (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,nregister::localreg[inst.reg1]
			,inst.scalar_a
		);
	}

	void emul_a (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::mul (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,nregister::localreg[inst.reg1] + offset
			,nregister::localreg[inst.reg2] + offset
		);
	}

	void emul_s (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::mul (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,nregister::localreg[inst.reg1] + offset
			,inst.scalar_a
		);
	}

	void bemul_a (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::mul (
			nregister::localreg[inst.reg0]
			,nregister::len
			,nregister::localreg[inst.reg1]
			,nregister::localreg[inst.reg2]
		);
	}

	void bemul_s (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::mul (
			nregister::localreg[inst.reg0]
			,nregister::len
			,nregister::localreg[inst.reg1]
			,inst.scalar_a
		);
	}
}