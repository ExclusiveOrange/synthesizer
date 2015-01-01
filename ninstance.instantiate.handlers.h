/* defines ninstance::instantiate handler functions */

#pragma once

//#include <mathimf.h>

namespace ninstance {
	char popreg(srpnstack *rpnstack) {
		char r = rpnstack->atom.back().atom.reg;
		rpnstack->atom.pop_back();
		return r;
	}

	double popval(srpnstack *rpnstack) {
		srpnatom *atom = &rpnstack->atom.back();
		double val = atom->type == NUM ? atom->atom.num : rpnstack->var[atom->atom.ivar];
		rpnstack->atom.pop_back();
		return val;
	}

	double gettopval(srpnstack *rpnstack) {
		srpnatom *atom = &rpnstack->atom.back();
		return atom->type == NUM ? atom->atom.num : rpnstack->var[atom->atom.ivar];
	}

	void settopval(srpnstack *rpnstack, double val) {
		srpnatom *atom = &rpnstack->atom.back();
		atom->type = NUM;
		atom->atom.num = val;
	}

	void pushinst(
		srpnstack *rpnstack
		,unsigned char opcode
		,unsigned char reg0
		,unsigned char reg1 = 0
		,unsigned char reg2 = 0
		,float scalar_a = 0.0
		,float scalar_b = 0.0
		,float scalar_c = 0.0
	) {
		ninstruction::sinst *i = &rpnstack->insts[rpnstack->curinst++];
		i->start = rpnstack->start;
		i->len = rpnstack->end - rpnstack->start;
		i->opcode = opcode;
		i->reg0 = reg0;
		i->reg1 = reg1;
		i->reg2 = reg2;
		i->scalar_a = scalar_a;
		i->scalar_b = scalar_b;
		i->scalar_c = scalar_c;
	}

	bool insthandler(srpnstack *rpnstack, char opcode) {
		double a, b, c;
		char r1, r2;
		switch (opcode) {
			// 0 parameters
			case 0x00: // noop
				pushinst(rpnstack, opcode, 0);
				break;
			case 0x01: // fill
				a = popval(rpnstack);
				pushinst(rpnstack, opcode, popreg(rpnstack), 0, 0, a);
				break;
			case 0x02: // add r r
				r2 = popreg(rpnstack);
				r1 = popreg(rpnstack);
				pushinst(rpnstack, opcode, popreg(rpnstack), r1, r2);
				break;
			case 0x03: // add r s
				a = popval(rpnstack);
				r1 = popreg(rpnstack);
				pushinst(rpnstack, opcode, popreg(rpnstack), r1, 0, a);
				break;
			case 0x04: // sub r r
				r2 = popreg(rpnstack);
				r1 = popreg(rpnstack);
				pushinst(rpnstack, opcode, popreg(rpnstack), r1, r2);
				break;
			case 0x05: // sub r s
				a = popval(rpnstack);
				r1 = popreg(rpnstack);
				pushinst(rpnstack, opcode, popreg(rpnstack), r1, 0, a);
				break;
			case 0x06: // sub s r
				r1 = popreg(rpnstack);
				a = popval(rpnstack);
				pushinst(rpnstack, opcode, popreg(rpnstack), r1, 0, a);
				break;
			case 0x07: // mul r r
				r2 = popreg(rpnstack);
				r1 = popreg(rpnstack);
				pushinst(rpnstack, opcode, popreg(rpnstack), r1, r2);
				break;
			case 0x08: // mul r s
				a = popval(rpnstack);
				r1 = popreg(rpnstack);
				pushinst(rpnstack, opcode, popreg(rpnstack), r1, 0, a);
				break;
			case 0x09: // addprod r r
				r2 = popreg(rpnstack);
				r1 = popreg(rpnstack);
				pushinst(rpnstack, opcode, popreg(rpnstack), r1, r2);
				break;
			case 0x0a: // addprod r s
				a = popval(rpnstack);
				r1 = popreg(rpnstack);
				pushinst(rpnstack, opcode, popreg(rpnstack), r1, 0, a);
				break;
			case 0x0b: // sine r r
			case 0x0f: // triangle
			case 0x13: // square
			case 0x17: // sawfore
			case 0x1b: // sawback
				r2 = popreg(rpnstack);
				r1 = popreg(rpnstack);
				a = popval(rpnstack);
				pushinst(rpnstack, opcode, popreg(rpnstack), r1, r2, a);
				break;
			case 0x0c: // sine r s
			case 0x10: // triangle
			case 0x14: // square
			case 0x18: // sawfore
			case 0x1c: // sawback
				b = popval(rpnstack);
				r1 = popreg(rpnstack);
				a = popval(rpnstack);
				pushinst(rpnstack, opcode, popreg(rpnstack), r1, 0, a, b);
				break;
			case 0x0d: // sine s r
			case 0x11: // triangle
			case 0x15: // square
			case 0x19: // sawfore
			case 0x1d: // sawback
				r1 = popreg(rpnstack);
				b = popval(rpnstack);
				a = popval(rpnstack);
				pushinst(rpnstack, opcode, popreg(rpnstack), r1, 0, a, b);
				break;
			case 0x0e: // sine s s
			case 0x12: // triangle
			case 0x16: // square
			case 0x1a: // sawfore
			case 0x1e: // sawback
				c = popval(rpnstack);
				b = popval(rpnstack);
				a = popval(rpnstack);
				pushinst(rpnstack, opcode, popreg(rpnstack), 0, 0, a, b, c);
				break;
			case 0x1f: // line
				b = popval(rpnstack);
				a = popval(rpnstack);
				pushinst(rpnstack, opcode, popreg(rpnstack), 0, 0, a, b);
				break;
			case 0x20: // muladd r r
				r2 = popreg(rpnstack);
				r1 = popreg(rpnstack);
				pushinst(rpnstack, opcode, popreg(rpnstack), r1, r2);
				break;
			case 0x21: // muladd r s
				a = popval(rpnstack);
				r1 = popreg(rpnstack);
				pushinst(rpnstack, opcode, popreg(rpnstack), r1, 0, a);
				break;
			case 0x22: // muladd s r
				r1 = popreg(rpnstack);
				a = popval(rpnstack);
				pushinst(rpnstack, opcode, popreg(rpnstack), r1, 0, a);
				break;
			case 0x23: // muladd s s
				b = popval(rpnstack);
				a = popval(rpnstack);
				pushinst(rpnstack, opcode, popreg(rpnstack), 0, 0, a, b);
				break;
			case 0x24: // noise
				b = popval(rpnstack);
				a = popval(rpnstack);
				pushinst(rpnstack, opcode, popreg(rpnstack), 0, 0, a, b);
				break;
			case 0x25: // exp
				r1 = popreg(rpnstack);
				pushinst(rpnstack, opcode, popreg(rpnstack), r1);
				break;
			case 0x26: // decay
				pushinst(rpnstack, opcode, popreg(rpnstack));
				break;
			case 0xf0: case 0xf1: case 0xf2: { // filters
				nfilter::cfilter *filter = 0;
				a = popval(rpnstack);
				switch (opcode) {
					case 0xf0: {
						int len = a < 1.0 / rpnstack->rate ? 1 : a > 1.0 ? (int)rpnstack->rate : (int)(a * rpnstack->rate);
						nfilter::cdelay *delay = new nfilter::cdelay;
						if (delay) delay->set(len);
						filter = delay;
					}	break;
					// until the Intel filters are replaced, best not to use them
					//case 0xf1: case 0xf2: {
					//	a /= rpnstack->rate;
					//	nfilter::ciir *iir = new nfilter::ciir;
					//	if (iir) opcode == 0xf1 ? iir->lowpass(a) : iir->highpass(a);
					//	filter = iir;
					//} break;
				}
				rpnstack->filters[rpnstack->curfilter++] = filter;
				{ unsigned int idelay = filter->getdelay();
					rpnstack->maxdelay = idelay > rpnstack->maxdelay ? idelay : rpnstack->maxdelay;
				}					
			} break;
			default:
				cerr << "unrecognized instruction in ninstance::insthandler()\n";
				return false;
		}
		return true;
	}

	bool ophandler(srpnstack *rpnstack, eoperator op) {
		double b = popval(rpnstack);

		switch (op) {
			case TIMESHORT:
				if (b >= rpnstack->end) {
					rpnstack->setstart(rpnstack->end);
					rpnstack->setend(b);
				}
				return true;
			case TIMEADD:
				if (b >= 0.0) {
					rpnstack->setstart(rpnstack->end);
					rpnstack->setend(rpnstack->end + b);
				}
				return true;				
		}

		double a = gettopval(rpnstack);

		switch (op) {
			case TIME:
				if (a <= b) {
					rpnstack->setstart(a);
					rpnstack->setend(b);
				}
				rpnstack->atom.pop_back();
				return true;
			case ADD: case SUB: case MUL: case DIV: case MOD: case POW: case RNDUNIFORM: case RNDGAUSSIAN:
				switch (op) {
					case ADD: a += b; break;
					case SUB: a -= b; break;
					case MUL: a *= b; break;
					case DIV: a /= b; break;
					case MOD: a = fmod(a, b); break;
					case POW: a = pow(a, b); break;
					case RNDUNIFORM: a = nrandom::uniform(a, b); break;
					case RNDGAUSSIAN: a = nrandom::gaussian(a, b); break;
				}
				break;
			case ASSIGN: case ADDASSIGN: case SUBASSIGN: case MULASSIGN: case DIVASSIGN: case MODASSIGN: case POWASSIGN:
				switch (op) {
					case ASSIGN: a = b; break;
					case ADDASSIGN: a += b; break;
					case SUBASSIGN: a -= b; break;
					case MULASSIGN: a *= b; break;
					case DIVASSIGN: a /= b; break;
					case MODASSIGN: a = fmod(a, b); break;
					case POWASSIGN: a = pow(a, b); break;
				}
				rpnstack->var[rpnstack->atom.back().atom.ivar] = a;
				break;
			default:
				//err = "unrecognized operator in ninstance::ophandler()";
				return false;
		}
		settopval(rpnstack, a);
		return true;
	}
}