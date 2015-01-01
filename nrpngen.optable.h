/* defines nrpngen operator table */

#pragma once

namespace nrpngen {
	enum eoperator : char {
		ADD = 0, SUB, MUL, DIV, MOD, POW, RNDUNIFORM, RNDGAUSSIAN,
		LPAREN, RPAREN,
		ASSIGN, ADDASSIGN, SUBASSIGN, MULASSIGN, DIVASSIGN, MODASSIGN, POWASSIGN,
		TIME, TIMESHORT, TIMEADD // these are segregated
	};

	struct soperator {
		char precedence;
		bool is_left_assoc;
		bool is_math;
		bool is_assign;
	} OPS[] = {
		{2, 1, 1, 0}, // ADD
		{2, 1, 1, 0}, // SUB
		{3, 1, 1, 0}, // MUL
		{3, 1, 1, 0}, // DIV
		{3, 1, 1, 0}, // MOD
		{5, 0, 1, 0}, // POW
		{4, 1, 1, 0}, // RNDUNIFORM
		{4, 1, 1, 0}, // RNDGAUSSIAN
		{0, 0, 0, 0}, // LPAREN
		{0, 0, 0, 0}, // RPAREN
		{1, 0, 0, 1}, // ASSIGN
		{1, 0, 0, 1}, // ADDASSIGN
		{1, 0, 0, 1}, // SUBASSIGN
		{1, 0, 0, 1}, // MULASSIGN
		{1, 0, 0, 1}, // DIVASSIGN
		{1, 0, 0, 1}, // MODASSIGN
		{1, 0, 0, 1}  // POWASSIGN
	};

	void readop(eoperator op) {
		switch (op) {
			case ADD: cout << "ADD"; break;
			case SUB: cout << "SUB"; break;
			case MUL: cout << "MUL"; break;
			case DIV: cout << "DIV"; break;
			case MOD: cout << "MOD"; break;
			case POW: cout << "POW"; break;
			case LPAREN: cout << "LPAREN"; break;
			case RPAREN: cout << "RPAREN"; break;
			case ASSIGN: cout << "ASSIGN"; break;
			case ADDASSIGN: cout << "ADDASSIGN"; break;
			case SUBASSIGN: cout << "SUBASSIGN"; break;
			case MULASSIGN: cout << "MULASSIGN"; break;
			case DIVASSIGN: cout << "DIVASSIGN"; break;
			case MODASSIGN: cout << "MODASSIGN"; break;
			case POWASSIGN: cout << "POWASSIGN"; break;
			case RNDUNIFORM: cout << "RNDUNIFORM"; break;
			case RNDGAUSSIAN: cout << "RNDGAUSSIAN"; break;
			case TIME: cout << "TIME"; break;
			case TIMESHORT: cout << "TIMESHORT"; break;
			case TIMEADD: cout << "TIMEADD"; break;
		}
	}
}