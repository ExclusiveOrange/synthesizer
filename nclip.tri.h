/* defines nclip::tri functions

validated

*/

#pragma once

namespace nclip {
	/////////////
	// no clip //
	/////////////
	void tri_aa (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		double a;
		nlowlevel::tri (
			nregister::localreg[inst.reg0] + offset
			,tto(inst.len)
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1] + offset
			,nregister::localreg[inst.reg2] + offset
			,a = 0.0
		);
	}

	void tri_as (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		double p;
		nlowlevel::tri (
			nregister::localreg[inst.reg0] + offset
			,tto(inst.len)
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1] + offset
			,p = inst.scalar_b
		);
	}

	void tri_sa (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		double a;
		nlowlevel::tri (
			nregister::localreg[inst.reg0] + offset
			,tto(inst.len)
			,nregister::rrate
			,inst.scalar_a
			,inst.scalar_b
			,nregister::localreg[inst.reg1] + offset
			,a = 0.0
		);
	}

	void tri_ss (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		double p;
		nlowlevel::tri (
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
	void btri_aa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::tri (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1]
			,nregister::localreg[inst.reg2]
			,acc.d
		);
	}

	void btri_as (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::tri (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1]
			,acc.d
		);
	}

	void btri_sa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::tri (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,nregister::rrate
			,inst.scalar_a
			,inst.scalar_b
			,nregister::localreg[inst.reg1]
			,acc.d
		);
	}

	void btri_ss (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::tri (
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
	void etri_aa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::tri (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1] + offset
			,nregister::localreg[inst.reg2] + offset
			,acc.d = 0.0
		);
	}

	void etri_as (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::tri (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1] + offset
			,acc.d = inst.scalar_b
		);
	}

	void etri_sa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::tri (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,nregister::rrate
			,inst.scalar_a
			,inst.scalar_b
			,nregister::localreg[inst.reg1] + offset
			,acc.d = 0.0
		);
	}

	void etri_ss (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::tri (
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
	void betri_aa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::tri (
			nregister::localreg[inst.reg0]
			,nregister::len
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1]
			,nregister::localreg[inst.reg2]
			,acc.d
		);
	}

	void betri_as (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::tri (
			nregister::localreg[inst.reg0]
			,nregister::len
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1]
			,acc.d
		);
	}

	void betri_sa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::tri (
			nregister::localreg[inst.reg0]
			,nregister::len
			,nregister::rrate
			,inst.scalar_a
			,inst.scalar_b
			,nregister::localreg[inst.reg1]
			,acc.d
		);
	}

	void betri_ss (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::tri (
			nregister::localreg[inst.reg0]
			,nregister::len
			,nregister::rrate
			,inst.scalar_a
			,inst.scalar_b
			,acc.d
		);
	}
}