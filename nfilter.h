/* defines namespace nfilter */

#pragma once

namespace nfilter {
	class cfilter {
		public:
			cfilter() {}
			virtual ~cfilter() {}

			virtual void filter (
				double *dest
				,const double *src
				,const int len
			) {}

			virtual int getdelay() { return 0; }
	};
}

#include "nfilter.cdelay.h"
//#include "nfilter.ciir.h"
