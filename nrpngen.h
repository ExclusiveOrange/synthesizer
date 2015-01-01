/* defines namespace nrpngen */

#pragma once

#include <cctype>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace nrpngen {
	using namespace std;
}

#include "nrpngen.insttable.h"
#include "nrpngen.optable.h"
#include "nrpngen.compact.h"

namespace nrpngen {
	class crpngen {
		protected:
			enum esymbol : char {
				INSTRUCTION, REGISTER, NAME, NUMBER, OPERATOR, COMMA, TERMINATOR, END, ERR
			};

			struct satom {
				union {
					double dub;
					char reg;
					union {
						char inst;
						char opcode;
					};
					eoperator op;
				};
				string name;
				esymbol symbol;
			};

			map<string, char> instmap;
			map<string, char> regmap;
			map<string, int> varmap;
			vector<eoperator> ops;
			istream *input;
			satom atom;
			esymbol symbol;
			int nlcount, colcount;

			void error(const char *message);
			bool get(char &ch);
			void putback(char ch);
			esymbol getsymbol();
			void collapse_ops();
			bool finish_instruction(); // and parameters
			bool expect_operand(bool orterminator = false);
			bool expect_operator(); // or terminator
		public:
			vector<satom> atomstack;
			int varcount;
			int instcount;
			int filtercount;
			bool end;

			crpngen();
			~crpngen();

			// don't forget to call these two functions before using an instance of this class
			void set_instnames();
			void set_regnames(int count);

			sstatement *compact();
			void readatom(satom &atom);
			void reset();
			void set_input(istream *newinput);
			bool statement();
	};
}

#include "nrpngen.readsource.h"
#include "nrpngen.funcs.h"