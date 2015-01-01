/* defines nrpngen source file reading functions */

#pragma once

#include <fstream>

namespace nrpngen {
	struct srpnsource {
		int size;
		int varcount;
		int instcount;
		int filtercount;
		sstatement **statement;

		srpnsource() {
			size = 0;
			varcount = 0;
			instcount = 0;
			filtercount = 0;
			statement = 0;
		}

		~srpnsource() {
			delete [] statement;
		}
	};

	void error(const char *message, const char *filename = 0) {
		cerr << "error in getrpnsource(): " << message;
		if (filename) cerr << filename;
		cerr << endl;
	}

	srpnsource *getrpnsource(crpngen &rpngen, const char *filename) {
		ifstream ifile(filename);
		if (!ifile.fail()) {
			rpngen.set_input(&ifile);
			vector<sstatement*> statements;
			while (rpngen.statement()) statements.push_back(rpngen.compact());
			rpngen.set_input(0);
			ifile.close();
			if (rpngen.end) {
				srpnsource *source = new srpnsource;
				char *err = "failed to allocate memory";
				if (source) {
					source->statement = new sstatement* [source->size = statements.size()];
					if (source->statement) {
						vector<sstatement*>::const_iterator iter = statements.begin();
						for (int i = 0; i < source->size; ++i, iter++) source->statement[i] = *iter;
						source->varcount = rpngen.varcount;
						source->instcount = rpngen.instcount;
						source->filtercount = rpngen.filtercount;
						return source;
					}
					delete source;
				}
				error(err);
			} else {
				vector<sstatement*>::const_iterator iter = statements.begin();
				for (; iter != statements.end(); iter++) delete *iter;
				error("error parsing file: ", filename);
			}
		} else error("unable to open file: ", filename);
		return 0;
	}
}