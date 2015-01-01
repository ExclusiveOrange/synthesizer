/* defines namespace nlowlevel */

#pragma once

#include "nlowlevel.add.h"
#include "nlowlevel.addprod.h"
#include "nlowlevel.copy.h"
#include "nlowlevel.decay.h"
#include "nlowlevel.exp.h"
#include "nlowlevel.fill.h"
#include "nlowlevel.line.h"
#include "nlowlevel.mul.h"
#include "nlowlevel.muladd.h"
#include "nlowlevel.noise.h"
#include "nlowlevel.sawb.h"
#include "nlowlevel.sawf.h"
#include "nlowlevel.sin.h"
#include "nlowlevel.sqr.h"
#include "nlowlevel.sub.h"
#include "nlowlevel.tri.h"

namespace nlowlevel {
	void
	init (
		void
	) {
		// todo: add initializers as needed
		init_decay();
		init_sin();
	}
}