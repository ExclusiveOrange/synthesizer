/* defines nrpngen functions for compact RPN statements */

#pragma once

namespace nrpngen {
	enum eatom : char {
		INST, REG, VAR, NUM, OP
	};

	union uatom {
		double num;
		int ivar;
		char reg;
		union {
			char inst;
			char opcode;
		};
		eoperator op;
	};

	struct sstatement {
		sstatement() {
			size = 0;
			type = 0;
			atom = 0;
		}
		~sstatement() {
			delete [] type;
			delete [] atom;
		}
		int size;
		eatom *type;
		uatom *atom;
	};

	void readatom(eatom type, uatom &atom) {
		switch (type) {
			case INST: cout << "INST: " << (int)atom.inst; break;
			case REG: cout << "REG: " << (int)atom.reg; break;
			case VAR: cout << "VAR: " << atom.ivar; break;
			case NUM: cout << "NUM: " << atom.num; break;
			case OP: cout << "OP: "; readop(atom.op); break;
		}
		cout << endl;
	}

	void readstatement(sstatement *statement) {
		if (!statement) return;
		for (int i = 0; i < statement->size; ++i) {
			readatom(statement->type[i], statement->atom[i]);
		}
	}
}