/* defines nclip::sin functions

validated

*/

#pragma once

namespace nclip {
	/////////////
	// no clip //
	/////////////
	void sin_aa (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		double a;
		nlowlevel::sin (
			nregister::localreg[inst.reg0] + offset
			,tto(inst.len)
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1] + offset
			,nregister::localreg[inst.reg2] + offset
			,a = 0.0
		);
	}

	void sin_as (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		double p;
		nlowlevel::sin (
			nregister::localreg[inst.reg0] + offset
			,tto(inst.len)
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1] + offset
			,p = inst.scalar_b
		);
	}

	void sin_sa (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		double a;
		nlowlevel::sin (
			nregister::localreg[inst.reg0] + offset
			,tto(inst.len)
			,nregister::rrate
			,inst.scalar_a
			,inst.scalar_b
			,nregister::localreg[inst.reg1] + offset
			,a = 0.0
		);
	}

	void sin_ss (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		double p;
		nlowlevel::sin (
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
	void bsin_aa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sin (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1]
			,nregister::localreg[inst.reg2]
			,acc.d
		);
	}

	void bsin_as (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sin (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1]
			,acc.d
		);
	}

	void bsin_sa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sin (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,nregister::rrate
			,inst.scalar_a
			,inst.scalar_b
			,nregister::localreg[inst.reg1]
			,acc.d
		);
	}

	void bsin_ss (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sin (
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
	void esin_aa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::sin (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1] + offset
			,nregister::localreg[inst.reg2] + offset
			,acc.d = 0.0
		);
	}

	void esin_as (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::sin (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1] + offset
			,acc.d = inst.scalar_b
		);
	}

	void esin_sa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::sin (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,nregister::rrate
			,inst.scalar_a
			,inst.scalar_b
			,nregister::localreg[inst.reg1] + offset
			,acc.d = 0.0
		);
	}

	void esin_ss (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::sin (
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
	void besin_aa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sin (
			nregister::localreg[inst.reg0]
			,nregister::len
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1]
			,nregister::localreg[inst.reg2]
			,acc.d
		);
	}

	void besin_as (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sin (
			nregister::localreg[inst.reg0]
			,nregister::len
			,nregister::rrate
			,inst.scalar_a
			,nregister::localreg[inst.reg1]
			,acc.d
		);
	}

	void besin_sa (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sin (
			nregister::localreg[inst.reg0]
			,nregister::len
			,nregister::rrate
			,inst.scalar_a
			,inst.scalar_b
			,nregister::localreg[inst.reg1]
			,acc.d
		);
	}

	void besin_ss (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::sin (
			nregister::localreg[inst.reg0]
			,nregister::len
			,nregister::rrate
			,inst.scalar_a
			,inst.scalar_b
			,acc.d
		);
	}
}