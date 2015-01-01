/* defines arrays of function pointers for clipping dispatch

function naming:
	no clipping:
		array fnoclip[]
		function func
	beginning only clip
		array fbclip[]
		function bfunc
	end only clip
		array feclip[]
		function efunc
	beginning and end clip
		array fclip[]
		function befunc

*/

#pragma once

#include "nclip.helper.h"

#include "nclip.add.h"
#include "nclip.addprod.h"
#include "nclip.decay.h"
#include "nclip.exp.h"
#include "nclip.fill.h"
#include "nclip.line.h"
#include "nclip.mul.h"
#include "nclip.muladd.h"
#include "nclip.noise.h"
#include "nclip.sawb.h"
#include "nclip.sawf.h"
#include "nclip.sin.h"
#include "nclip.sqr.h"
#include "nclip.sub.h"
#include "nclip.tri.h"

namespace nclip {
	const int functioncount = 0x27;

	void noop (
		const double start
		,const ninstruction::sinst &inst
	) {}

	void noop (
		const double start
		,const ninstruction::sinst &inst
		,uacc &acc
	) {}

	void (* const fnoclip[functioncount]) (
		const double
		,const ninstruction::sinst &inst
	) = {
		noop                     // 0x00
		,fill                    // 0x01
		,add_a                   // 0x02
		,add_s                   // 0x03
		,sub_a                   // 0x04
		,sub_s                   // 0x05
		,sub_r                   // 0x06
		,mul_a                   // 0x07
		,mul_s                   // 0x08
		,addprod_a               // 0x09
		,addprod_s               // 0x0a
		,sin_aa                  // 0x0b
		,sin_as                  // 0x0c
		,sin_sa                  // 0x0d
		,sin_ss                  // 0x0e
		,tri_aa                  // 0x0f
		,tri_as                  // 0x10
		,tri_sa                  // 0x11
		,tri_ss                  // 0x12
		,sqr_aa                  // 0x13
		,sqr_as                  // 0x14
		,sqr_sa                  // 0x15
		,sqr_ss                  // 0x16
		,sawf_aa                 // 0x17
		,sawf_as                 // 0x18
		,sawf_sa                 // 0x19
		,sawf_ss                 // 0x1a
		,sawb_aa                 // 0x1b
		,sawb_as                 // 0x1c
		,sawb_sa                 // 0x1d
		,sawb_ss                 // 0x1e
		,line                    // 0x1f
		,muladd_aa               // 0x20
		,muladd_as               // 0x21
		,muladd_sa               // 0x22
		,muladd_ss               // 0x23
		,noise                   // 0x24
		,exp                     // 0x25
		,decay                   // 0x26
	};

	void (* const fbclip[functioncount]) (
		const double
		,const ninstruction::sinst &inst
		,uacc&
	) = {
		noop                     // 0x00
		,bfill                   // 0x01
		,badd_a                  // 0x02
		,badd_s                  // 0x03
		,bsub_a                  // 0x04
		,bsub_s                  // 0x05
		,bsub_r                  // 0x06
		,bmul_a                  // 0x07
		,bmul_s                  // 0x08
		,baddprod_a              // 0x09
		,baddprod_s              // 0x0a
		,bsin_aa                 // 0x0b
		,bsin_as                 // 0x0c
		,bsin_sa                 // 0x0d
		,bsin_ss                 // 0x0e
		,btri_aa                 // 0x0f
		,btri_as                 // 0x10
		,btri_sa                 // 0x11
		,btri_ss                 // 0x12
		,bsqr_aa                 // 0x13
		,bsqr_as                 // 0x14
		,bsqr_sa                 // 0x15
		,bsqr_ss                 // 0x16
		,bsawf_aa                // 0x17
		,bsawf_as                // 0x18
		,bsawf_sa                // 0x19
		,bsawf_ss                // 0x1a
		,bsawb_aa                // 0x1b
		,bsawb_as                // 0x1c
		,bsawb_sa                // 0x1d
		,bsawb_ss                // 0x1e
		,bline                   // 0x1f
		,bmuladd_aa              // 0x20
		,bmuladd_as              // 0x21
		,bmuladd_sa              // 0x22
		,bmuladd_ss              // 0x23
		,bnoise                  // 0x24
		,bexp                    // 0x25
		,bdecay                  // 0x26
	};

	void (* const feclip[functioncount]) (
		const double
		,const ninstruction::sinst &inst
		,uacc&
	) = {
		noop                     // 0x00
		,efill                   // 0x01
		,eadd_a                  // 0x02
		,eadd_s                  // 0x03
		,esub_a                  // 0x04
		,esub_s                  // 0x05
		,esub_r                  // 0x06
		,emul_a                  // 0x07
		,emul_s                  // 0x08
		,eaddprod_a              // 0x09
		,eaddprod_s              // 0x0a
		,esin_aa                 // 0x0b
		,esin_as                 // 0x0c
		,esin_sa                 // 0x0d
		,esin_ss                 // 0x0e
		,etri_aa                 // 0x0f
		,etri_as                 // 0x10
		,etri_sa                 // 0x11
		,etri_ss                 // 0x12
		,esqr_aa                 // 0x13
		,esqr_as                 // 0x14
		,esqr_sa                 // 0x15
		,esqr_ss                 // 0x16
		,esawf_aa                // 0x17
		,esawf_as                // 0x18
		,esawf_sa                // 0x19
		,esawf_ss                // 0x1a
		,esawb_aa                // 0x1b
		,esawb_as                // 0x1c
		,esawb_sa                // 0x1d
		,esawb_ss                // 0x1e
		,eline                   // 0x1f
		,emuladd_aa              // 0x20
		,emuladd_as              // 0x21
		,emuladd_sa              // 0x22
		,emuladd_ss              // 0x23
		,enoise                  // 0x24
		,eexp                    // 0x25
		,edecay                  // 0x26
	};

	void (* const fclip[functioncount]) (
		const double
		,const ninstruction::sinst &inst
		,uacc&
	) = {
		noop                     // 0x00
		,befill                  // 0x01
		,beadd_a                 // 0x02
		,beadd_s                 // 0x03
		,besub_a                 // 0x04
		,besub_s                 // 0x05
		,besub_r                 // 0x06
		,bemul_a                 // 0x07
		,bemul_s                 // 0x08
		,beaddprod_a             // 0x09
		,beaddprod_s             // 0x0a
		,besin_aa                // 0x0b
		,besin_as                // 0x0c
		,besin_sa                // 0x0d
		,besin_ss                // 0x0e
		,betri_aa                // 0x0f
		,betri_as                // 0x10
		,betri_sa                // 0x11
		,betri_ss                // 0x12
		,besqr_aa                // 0x13
		,besqr_as                // 0x14
		,besqr_sa                // 0x15
		,besqr_ss                // 0x16
		,besawf_aa               // 0x17
		,besawf_as               // 0x18
		,besawf_sa               // 0x19
		,besawf_ss               // 0x1a
		,besawb_aa               // 0x1b
		,besawb_as               // 0x1c
		,besawb_sa               // 0x1d
		,besawb_ss               // 0x1e
		,beline                  // 0x1f
		,bemuladd_aa             // 0x20
		,bemuladd_as             // 0x21
		,bemuladd_sa             // 0x22
		,bemuladd_ss             // 0x23
		,benoise                 // 0x24
		,beexp                   // 0x25
		,bedecay                 // 0x26
	};
}