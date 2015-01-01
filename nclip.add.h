/* defines nclip::add functions

validated

*/

#pragma once

namespace nclip {
	void add_a (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		nlowlevel::add (
			nregister::localreg[inst.reg0] + offset
			,tto(inst.len)
			,nregister::localreg[inst.reg1] + offset
			,nregister::localreg[inst.reg2] + offset
		);
	}

	void add_s (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		nlowlevel::add (
			nregister::localreg[inst.reg0] + offset
			,tto(inst.len)
			,nregister::localreg[inst.reg1] + offset
			,inst.scalar_a
		);
	}

	void badd_a (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::add (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,nregister::localreg[inst.reg1]
			,nregister::localreg[inst.reg2]
		);
	}

	void badd_s (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::add (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,nregister::localreg[inst.reg1]
			,inst.scalar_a
		);			
	}

	void eadd_a (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::add (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,nregister::localreg[inst.reg1] + offset
			,nregister::localreg[inst.reg2] + offset
		);			
	}

	void eadd_s (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::add (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,nregister::localreg[inst.reg1] + offset
			,inst.scalar_a
		);
	}

	void beadd_a (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::add (
			nregister::localreg[inst.reg0]
			,nregister::len
			,nregister::localreg[inst.reg1]
			,nregister::localreg[inst.reg2]
		);
	}

	void beadd_s (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::add (
			nregister::localreg[inst.reg0]
			,nregister::len
			,nregister::localreg[inst.reg1]
			,inst.scalar_a
		);
	}
}