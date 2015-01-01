/* defines nclip::sqr functions

validated

*/

#pragma once

namespace nclip {
	/////////////
	// no clip //
	/////////////
	void sqr_aa (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		double a;
		nlowlevel::sqr (
			nregister::localreg[inst.reg0] + offset
			,tto(inst.len)
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1] + offset
			,nregister::localreg[inst.reg2] + offset
			,a = 0.0
		);
	}

	void sqr_as (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		double p;
		nlowlevel::sqr (
			nregister::localreg[inst.reg0] + offset
			,tto(inst.len)
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1] + offset
			,p = inst.scalar_b
		);
	}

	void sqr_sa (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		double a;
		nlowlevel::sqr (
			nregister::localreg[inst.reg0] + offset
			,tto(inst.len)
			,nregister::rrate
			,inst.scalar_a
			,inst.scalar_b
			,nregister::localreg[inst.reg1] + offset
			,a = 0.0
		);
	}

	void sqr_ss (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		double p;
		nlowlevel::sqr (
			nregister::localreg[inst.reg0] + offset
			,tto(inst.len)
			,nregister::rrate
			,inst.scalar_a
			,inst.scalar_b
			,p = inst.scalar_c
		);
	}

	/////////////////////////
	// beginning only clip //
	/////////////////////////
	void bsqr_aa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sqr (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1]
			,nregister::localreg[inst.reg2]
			,acc.d
		);
	}

	void bsqr_as (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sqr (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1]
			,acc.d
		);
	}

	void bsqr_sa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sqr (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,nregister::rrate
			,inst.scalar_a
			,inst.scalar_b
			,nregister::localreg[inst.reg1]
			,acc.d
		);
	}

	void bsqr_ss (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sqr (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,nregister::rrate
			,inst.scalar_a
			,inst.scalar_b
			,acc.d
		);
	}

	///////////////////
	// end only clip //
	///////////////////
	void esqr_aa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::sqr (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1] + offset
			,nregister::localreg[inst.reg2] + offset
			,acc.d = 0.0
		);
	}

	void esqr_as (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::sqr (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1] + offset
			,acc.d = inst.scalar_b
		);
	}

	void esqr_sa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::sqr (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,nregister::rrate
			,inst.scalar_a
			,inst.scalar_b
			,nregister::localreg[inst.reg1] + offset
			,acc.d = 0.0
		);
	}

	void esqr_ss (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::sqr (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,nregister::rrate
			,inst.scalar_a
			,inst.scalar_b
			,acc.d = inst.scalar_c
		);
	}

	////////////////////
	// clip both ends //
  ////////////////////
	void besqr_aa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sqr (
			nregister::localreg[inst.reg0]
			,nregister::len
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1]
			,nregister::localreg[inst.reg2]
			,acc.d
		);
	}

	void besqr_as (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sqr (
			nregister::localreg[inst.reg0]
			,nregister::len
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1]
			,acc.d
		);
	}

	void besqr_sa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sqr (
			nregister::localreg[inst.reg0]
			,nregister::len
			,nregister::rrate
			,inst.scalar_a
			,inst.scalar_b
			,nregister::localreg[inst.reg1]
			,acc.d
		);
	}

	void besqr_ss (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sqr (
			nregister::localreg[inst.reg0]
			,nregister::len
			,nregister::rrate
			,inst.scalar_a
			,inst.scalar_b
			,acc.d
		);
	}
}