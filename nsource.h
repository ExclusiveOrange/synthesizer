/* defines namespace nsource */

#pragma once

#include "nrpngen.h"

namespace nsource {
	struct ssource {
		nrpngen::srpnsource *rpnsource;

		ssource() {
			rpnsource = 0;
		}

		~ssource() {
			delete rpnsource;
		}
	};
}