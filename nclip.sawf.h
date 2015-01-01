/* defines nclip::sawf functions

validated

*/

#pragma once

namespace nclip {
	/////////////
	// no clip //
	/////////////
	void sawf_aa (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		double a;
		nlowlevel::sawf (
			nregister::localreg[inst.reg0] + offset
			,tto(inst.len)
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1] + offset
			,nregister::localreg[inst.reg2] + offset
			,a = 0.0
		);
	}

	void sawf_as (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		double p;
		nlowlevel::sawf (
			nregister::localreg[inst.reg0] + offset
			,tto(inst.len)
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1] + offset
			,p = inst.scalar_b
		);
	}

	void sawf_sa (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		double a;
		nlowlevel::sawf (
			nregister::localreg[inst.reg0] + offset
			,tto(inst.len)
			,nregister::rrate
			,inst.scalar_a
			,inst.scalar_b
			,nregister::localreg[inst.reg1] + offset
			,a = 0.0
		);
	}

	void sawf_ss (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		double p;
		nlowlevel::sawf (
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
	void bsawf_aa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sawf (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1]
			,nregister::localreg[inst.reg2]
			,acc.d
		);
	}

	void bsawf_as (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sawf (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1]
			,acc.d
		);
	}

	void bsawf_sa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sawf (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,nregister::rrate
			,inst.scalar_a
			,inst.scalar_b
			,nregister::localreg[inst.reg1]
			,acc.d
		);
	}

	void bsawf_ss (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sawf (
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
	void esawf_aa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::sawf (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1] + offset
			,nregister::localreg[inst.reg2] + offset
			,acc.d = 0.0
		);
	}

	void esawf_as (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::sawf (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1] + offset
			,acc.d = inst.scalar_b
		);
	}

	void esawf_sa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::sawf (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,nregister::rrate
			,inst.scalar_a
			,inst.scalar_b
			,nregister::localreg[inst.reg1] + offset
			,acc.d = 0.0
		);
	}

	void esawf_ss (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::sawf (
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
	void besawf_aa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sawf (
			nregister::localreg[inst.reg0]
			,nregister::len
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1]
			,nregister::localreg[inst.reg2]
			,acc.d
		);
	}

	void besawf_as (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sawf (
			nregister::localreg[inst.reg0]
			,nregister::len
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1]
			,acc.d
		);
	}

	void besawf_sa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sawf (
			nregister::localreg[inst.reg0]
			,nregister::len
			,nregister::rrate
			,inst.scalar_a
			,inst.scalar_b
			,nregister::localreg[inst.reg1]
			,acc.d
		);
	}

	void besawf_ss (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sawf (
			nregister::localreg[inst.reg0]
			,nregister::len
			,nregister::rrate
			,inst.scalar_a
			,inst.scalar_b
			,acc.d
		);
	}
}