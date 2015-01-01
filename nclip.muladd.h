/* defines nclip::muladd functions

validated

*/

#pragma once

namespace nclip {
	/////////////
	// no clip //
	/////////////
	void muladd_aa (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		nlowlevel::muladd (
			nregister::localreg[inst.reg0] + offset
			,tto(inst.len)
			,nregister::localreg[inst.reg1] + offset
			,nregister::localreg[inst.reg2] + offset
		);
	}

	void muladd_as (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		nlowlevel::muladd (
			nregister::localreg[inst.reg0] + offset
			,tto(inst.len)
			,nregister::localreg[inst.reg1] + offset
			,inst.scalar_a
		);
	}

	void muladd_sa (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		nlowlevel::muladd (
			nregister::localreg[inst.reg0] + offset
			,tto(inst.len)
			,inst.scalar_a
			,nregister::localreg[inst.reg1] + offset
		);
	}

	void muladd_ss (
		const double start
		,const ninstruction::sinst &inst
	) {
		nlowlevel::muladd (
			nregister::localreg[inst.reg0] + tto(inst.start - start)
			,tto(inst.len)
			,inst.scalar_a
			,inst.scalar_b
		);
	}

	/////////////////////////
	// beginning only clip //
	/////////////////////////
	void bmuladd_aa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::muladd (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,nregister::localreg[inst.reg1]
			,nregister::localreg[inst.reg2]
		);
	}

	void bmuladd_as (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::muladd (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,nregister::localreg[inst.reg1]
			,inst.scalar_a
		);
	}

	void bmuladd_sa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::muladd (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,inst.scalar_a
			,nregister::localreg[inst.reg1]
		);
	}

	void bmuladd_ss (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::muladd (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,inst.scalar_a
			,inst.scalar_b
		);
	}

	///////////////////
	// end only clip //
	///////////////////
	void emuladd_aa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::muladd (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,nregister::localreg[inst.reg1] + offset
			,nregister::localreg[inst.reg2] + offset
		);
	}

	void emuladd_as (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::muladd (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,nregister::localreg[inst.reg1] + offset
			,inst.scalar_a
		);
	}

	void emuladd_sa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::muladd (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,inst.scalar_a
			,nregister::localreg[inst.reg1] + offset
		);
	}

	void emuladd_ss (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::muladd (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,inst.scalar_a
			,inst.scalar_b
		);
	}

	////////////////////
	// clip both ends //
	////////////////////
	void bemuladd_aa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::muladd (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,nregister::localreg[inst.reg1]
			,nregister::localreg[inst.reg2]
		);
	}

	void bemuladd_as (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::muladd (
			nregister::localreg[inst.reg0]
			,nregister::len
			,nregister::localreg[inst.reg1]
			,inst.scalar_a
		);
	}

	void bemuladd_sa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::muladd (
			nregister::localreg[inst.reg0]
			,nregister::len
			,inst.scalar_a
			,nregister::localreg[inst.reg1]
		);
	}

	void bemuladd_ss (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::muladd (
			nregister::localreg[inst.reg0]
			,nregister::len
			,inst.scalar_a
			,inst.scalar_b
		);
	}
}