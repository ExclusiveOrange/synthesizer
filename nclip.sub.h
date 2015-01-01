/* defines nclip::sub functions

validated

*/

#pragma once

namespace nclip {
	void sub_a (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		nlowlevel::sub (
			nregister::localreg[inst.reg0] + offset
			,tto(inst.len)
			,nregister::localreg[inst.reg1] + offset
			,nregister::localreg[inst.reg2] + offset
		);
	}

	void sub_s (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		nlowlevel::sub (
			nregister::localreg[inst.reg0] + offset
			,tto(inst.len)
			,nregister::localreg[inst.reg1] + offset
			,inst.scalar_a
		);
	}

	void sub_r (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		nlowlevel::sub (
			nregister::localreg[inst.reg0] + offset
			,tto(inst.len)
			,inst.scalar_a
			,nregister::localreg[inst.reg1] + offset
		);
	}

	void bsub_a (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sub (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,nregister::localreg[inst.reg1]
			,nregister::localreg[inst.reg2]
		);
	}

	void bsub_s (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sub (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,nregister::localreg[inst.reg1]
			,inst.scalar_a
		);
	}

	void bsub_r (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sub (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,inst.scalar_a
			,nregister::localreg[inst.reg1]
		);
	}

	void esub_a (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::sub (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,nregister::localreg[inst.reg1] + offset
			,nregister::localreg[inst.reg2] + offset
		);
	}

	void esub_s (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::sub (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,nregister::localreg[inst.reg1] + offset
			,inst.scalar_a
		);
	}

	void esub_r (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::sub (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,inst.scalar_a
			,nregister::localreg[inst.reg1] + offset
		);
	}

	void besub_a (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sub (
			nregister::localreg[inst.reg0]
			,nregister::len
			,nregister::localreg[inst.reg1]
			,nregister::localreg[inst.reg2]
		);
	}

	void besub_s (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sub (
			nregister::localreg[inst.reg0]
			,nregister::len
			,nregister::localreg[inst.reg1]
			,inst.scalar_a
		);
	}

	void besub_r (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sub (
			nregister::localreg[inst.reg0]
			,nregister::len
			,inst.scalar_a
			,nregister::localreg[inst.reg1]
		);
	}
}