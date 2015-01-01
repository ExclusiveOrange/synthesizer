/* defines nclip::sawb functions

validated

*/

#pragma once

namespace nclip {
	/////////////
	// no clip //
	/////////////
	void sawb_aa (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		double a;
		nlowlevel::sawb (
			nregister::localreg[inst.reg0] + offset
			,tto(inst.len)
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1] + offset
			,nregister::localreg[inst.reg2] + offset
			,a = 0.0
		);
	}

	void sawb_as (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		double p;
		nlowlevel::sawb (
			nregister::localreg[inst.reg0] + offset
			,tto(inst.len)
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1] + offset
			,p = inst.scalar_b
		);
	}

	void sawb_sa (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		double a;
		nlowlevel::sawb (
			nregister::localreg[inst.reg0] + offset
			,tto(inst.len)
			,nregister::rrate
			,inst.scalar_a
			,inst.scalar_b
			,nregister::localreg[inst.reg1] + offset
			,a = 0.0
		);
	}

	void sawb_ss (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		double p;
		nlowlevel::sawb (
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
	void bsawb_aa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sawb (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1]
			,nregister::localreg[inst.reg2]
			,acc.d
		);
	}

	void bsawb_as (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sawb (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1]
			,acc.d
		);
	}

	void bsawb_sa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sawb (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,nregister::rrate
			,inst.scalar_a
			,inst.scalar_b
			,nregister::localreg[inst.reg1]
			,acc.d
		);
	}

	void bsawb_ss (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sawb (
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
	void esawb_aa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::sawb (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1] + offset
			,nregister::localreg[inst.reg2] + offset
			,acc.d = 0.0
		);
	}

	void esawb_as (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::sawb (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1] + offset
			,acc.d = inst.scalar_b
		);
	}

	void esawb_sa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::sawb (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,nregister::rrate
			,inst.scalar_a
			,inst.scalar_b
			,nregister::localreg[inst.reg1] + offset
			,acc.d = 0.0
		);
	}

	void esawb_ss (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::sawb (
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
	void besawb_aa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sawb (
			nregister::localreg[inst.reg0]
			,nregister::len
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1]
			,nregister::localreg[inst.reg2]
			,acc.d
		);
	}

	void besawb_as (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sawb (
			nregister::localreg[inst.reg0]
			,nregister::len
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1]
			,acc.d
		);
	}

	void besawb_sa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sawb (
			nregister::localreg[inst.reg0]
			,nregister::len
			,nregister::rrate
			,inst.scalar_a
			,inst.scalar_b
			,nregister::localreg[inst.reg1]
			,acc.d
		);
	}

	void besawb_ss (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sawb (
			nregister::localreg[inst.reg0]
			,nregister::len
			,nregister::rrate
			,inst.scalar_a
			,inst.scalar_b
			,acc.d
		);
	}
}