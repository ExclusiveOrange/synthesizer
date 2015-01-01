/* defines nclip::addprod functions

validated

*/

#pragma once

namespace nclip {
	void addprod_a (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		nlowlevel::addprod (
			nregister::localreg[inst.reg0] + offset
			,tto(inst.len)
			,nregister::localreg[inst.reg1] + offset
			,nregister::localreg[inst.reg2] + offset
		);
	}

	void addprod_s (
		const double start
		,const ninstruction::sinst &inst
	) {
		int offset = tto(inst.start - start);
		nlowlevel::addprod (
			nregister::localreg[inst.reg0] + offset
			,tto(inst.len)
			,nregister::localreg[inst.reg1] + offset
			,inst.scalar_a
		);
	}

	void baddprod_a (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::addprod (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,nregister::localreg[inst.reg1]
			,nregister::localreg[inst.reg2]
		);
	}

	void baddprod_s (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::addprod (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,nregister::localreg[inst.reg1]
			,inst.scalar_a
		);
	}

	void eaddprod_a (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::addprod (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,nregister::localreg[inst.reg1] + offset
			,nregister::localreg[inst.reg2] + offset
		);
	}

	void eaddprod_s (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		nlowlevel::addprod (
			nregister::localreg[inst.reg0] + offset
			,nregister::len - offset
			,nregister::localreg[inst.reg1] + offset
			,inst.scalar_a
		);
	}

	void beaddprod_a (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::addprod (
			nregister::localreg[inst.reg0]
			,nregister::len
			,nregister::localreg[inst.reg1]
			,nregister::localreg[inst.reg2]
		);
	}

	void beaddprod_s (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::addprod (
			nregister::localreg[inst.reg0]
			,nregister::len
			,nregister::localreg[inst.reg1]
			,inst.scalar_a
		);
	}
}