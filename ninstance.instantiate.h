/* defines ninstance::instantiate function */

#pragma once

#include <vector>

namespace ninstance {
	using namespace std;
	using namespace nrpngen;

	struct srpnatom {
		uatom atom;
		eatom type;
	};

	struct srpnstack {
		double *var;
		double start, end;
		double minstart, maxend;
		unsigned int maxdelay;
		double rate;
		double magnitude;
		vector<srpnatom> atom;
		ninstruction::sinst *insts;
		nfilter::cfilter **filters;
		int curinst;
		int curfilter;

		srpnstack() {
			var = 0;
			start = 0.0;
			end = 0.0;
			minstart = 0.0;
			maxend = 0.0;
			maxdelay = 0;
			rate = 48000.0; // to avoid divide by zero if this were 0
			insts = 0;
			filters = 0;
			curinst = 0;
			curfilter = 0;
		}

		~srpnstack() {
			delete [] var;
		}

		void setstart(double newstart) {
			start = newstart;
			minstart = start < minstart ? start : minstart;
		}

		void setend(double newend) {
			end = newend;
			maxend = end > maxend ? end : maxend;
		}
	};

	bool insthandler(srpnstack *rpnstack, char opcode);
	bool ophandler(srpnstack *rpnstack, eoperator op);
}

#include "ninstance.instantiate.handlers.h"

namespace ninstance {
	sinstance *instantiate(srpnsource *rpnsource) {
		if (!rpnsource) return 0;

		char *err = "failed to allocate memory in ninstance::instantiate()";
		srpnstack *rpnstack = new srpnstack;
		if (rpnstack) {
			double *var = new double[rpnsource->varcount];
			for (int i = 0; i < rpnsource->varcount; ++i) var[i] = 0.0;
			if (var) {
				ninstruction::sinst *insts = new ninstruction::sinst[rpnsource->instcount];
				if (insts) {
					nfilter::cfilter **filters = new nfilter::cfilter*[rpnsource->filtercount];
					if (filters) {
						rpnstack->var = var;
						rpnstack->insts = insts;
						rpnstack->filters = filters;
						bool good = true;
						for (int s = 0; s < rpnsource->size && good; ++s) { // iterate through all statements
							for (int i = 0; i < rpnsource->statement[s]->size && good; ++i) { // iterate through all atoms
								srpnatom atom;
								atom.atom = rpnsource->statement[s]->atom[i];
								atom.type = rpnsource->statement[s]->type[i];
								//nrpngen::readatom(atom.type, atom.atom);
								switch (atom.type) {
									case INST:
										good = insthandler(rpnstack, atom.atom.inst);
										break;
									case REG:
									case VAR:
									case NUM:
										rpnstack->atom.push_back(atom);
										break;
									case OP:
										good = ophandler(rpnstack, atom.atom.op);
										break;
									default:
										err = "unexpected atom type in rpnsource in ninstance::instantiate";
										good = false;
										break;
								}
							}
						}
						if (good) {
							sinstance *instance = new sinstance;
							if (instance) {
								nclip::uacc *accumulators = new nclip::uacc[rpnsource->instcount];
								if (accumulators) {
									for (int i = 0; i < rpnsource->instcount; ++i) accumulators[i].d = 0.0;
									instance->instduration = rpnstack->maxend - rpnstack->minstart;
									instance->filterduration = instance->instduration + (double)rpnstack->maxdelay * nregister::rrate;
									instance->insts = insts;
									instance->accumulators = accumulators;
									instance->filters = filters;
									instance->instcount = rpnsource->instcount;
									instance->filtercount = rpnsource->filtercount;
									delete rpnstack;
									return instance;
								}
								delete instance;							
							}
						}
						delete [] filters;
					}
					delete [] insts;
				}
				delete [] var;
			}
			delete rpnstack;
		}
		cerr << err << endl;
		return 0;
	}
}