/* defines nclip::decay functions */

#pragma once

namespace nclip {
	void decay (
		const double start
		,const ninstruction::sinst &inst
	) {
		nlowlevel::decay (
			nregister::localreg[inst.reg0] + tto(inst.start - start)
			,tto(inst.len)
			,0.0
			,1.0
		);
	}

	void bdecay (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		nlowlevel::decay (
			nregister::localreg[inst.reg0]
			,tto(inst.start + inst.len - start)
			,acc.d
			,1.0
		);
	}

	void edecay (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		int offset = tto(inst.start - start);
		acc.i = nregister::len - offset;
		acc.d = (nregister::rrate * acc.i) / inst.len;
		nlowlevel::decay (
			nregister::localreg[inst.reg0] + offset
			,acc.i
			,0.0
			,acc.d
		);
	}

	void bedecay (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		acc.i += nregister::len;
		double end = (nregister::rrate * acc.i) / inst.len;
		nlowlevel::decay (
			nregister::localreg[inst.reg0]
			,nregister::len
			,acc.d
			,end
		);
		acc.d = end;
	}
}