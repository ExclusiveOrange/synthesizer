/* defines nrpngen::crpngen functions */

#pragma once

namespace nrpngen {
	void crpngen::error(const char *message) {
		cerr << "error at line " << nlcount << ", column " << colcount << ": " << message << endl;
	}

	bool crpngen::get(char &ch) {
		if (!input->get(ch)) return false;
		if (ch == '\n') {
			++nlcount;
			colcount = 1;
		} else ++colcount;
		return true;
	}

	void crpngen::putback(char ch) {
		input->putback(ch);
		colcount -= colcount > 1 ? 1 : 0;
	}

	crpngen::esymbol crpngen::getsymbol() {
		char ch;
		do {
			if (!get(ch)) return symbol = END;
			if (ch == '\'') { // end of line comment
				do if (!get(ch)) return symbol = END; while (ch != '\n');
			} else if (ch == '\"') { // multi line comment
				do if (!get(ch)) return symbol = END; while (ch != '\"');
				if (!get(ch)) return symbol = END;
			}
		} while (ch == '\n' || isspace((unsigned char)ch));
		if (isdigit((unsigned char)ch) || ch == '.') {
			putback(ch);
			atom.symbol = NUMBER;
			streamoff i = input->tellg();
			*input >> atom.dub;
			colcount += input->tellg() - i;
			return symbol = NUMBER;
		} else if (isalpha((unsigned char)ch)) {
			atom.name = ch;
			while (get(ch) && isalnum((unsigned char)ch)) atom.name.push_back(ch);
			putback(ch);
			{ map<string, char>::const_iterator iter;
				if ((iter = regmap.find(atom.name)) != regmap.end()) {
					atom.symbol = REGISTER;
					atom.reg = iter->second;
					atom.name.clear();
					return symbol = REGISTER; 
				}
				if ((iter = instmap.find(atom.name)) != instmap.end()) {
					atom.symbol = INSTRUCTION;
					atom.inst = iter->second;
					atom.name.clear();
					return symbol = INSTRUCTION;
				}
			}
			atom.symbol = NAME;
			return symbol = NAME;
		} else {
			switch (ch) {
				case ',':
					return symbol = COMMA;
				case ';':
					return symbol = TERMINATOR;
				case '-': {
					char ch2;
					if (!get(ch2)) return symbol = END;
					if (isdigit((unsigned char)ch2) || ch2 == '.') {
						putback(ch2);
						atom.symbol = NUMBER;
						streamoff i = input->tellg();
						*input >> atom.dub;
						atom.dub = -atom.dub;
						colcount += input->tellg() - i;
						return symbol = NUMBER;
					} else putback(ch2);
				}
				case '+': case '*': case '/': case '%': case '^': {
					char ch2;
					if (!get(ch2)) return symbol = END;
					if (ch2 == '=') {
						atom.symbol = OPERATOR;
						switch (ch) {
							case '+': atom.op = ADDASSIGN; break;
							case '-': atom.op = SUBASSIGN; break;
							case '*': atom.op = MULASSIGN; break;
							case '/': atom.op = DIVASSIGN; break;
							case '%': atom.op = MODASSIGN; break;
							case '^': atom.op = POWASSIGN; break;
						}
						return symbol = OPERATOR;
					} else putback(ch2);
				}
				case '(': case ')': case '=': case '#': case '@':
					atom.symbol = OPERATOR;
					switch (ch) {
						case '+': atom.op = ADD; break;
						case '-': atom.op = SUB; break;
						case '*': atom.op = MUL; break;
						case '/': atom.op = DIV; break;
						case '%': atom.op = MOD; break;
						case '^': atom.op = POW; break;
						case '#': atom.op = RNDUNIFORM; break;
						case '@': atom.op = RNDGAUSSIAN; break;
						case '(': atom.op = LPAREN; break;
						case ')': atom.op = RPAREN; break;
						case '=': atom.op = ASSIGN; break;
					}
					return symbol = OPERATOR;
			}
			error("invalid symbol");
			return symbol = ERR;
		}
	}

	void crpngen::collapse_ops() {
		if (!ops.size()) return;
		atom.symbol = OPERATOR;
		while (ops.size()) {
			atom.op = ops.back();
			atomstack.push_back(atom);
			ops.pop_back();
		}
	}

	bool crpngen::finish_instruction() {
		sinst *inst = &INSTS[atom.inst];
		int version = 0;
		if (inst->numparams) {
			for (int iparam = 0; iparam < inst->numparams; ++iparam) {
				bool isreg = 0;
				getsymbol();
				switch (symbol) {
					case REGISTER:
						atomstack.push_back(atom);
						isreg = 1;
						getsymbol();
						break;
					case OPERATOR:
						if (atom.op != LPAREN) break;
					case NAME:
					case NUMBER:
						if (!expect_operand()) return false;
						collapse_ops();
						isreg = 0;
						break;
					default:
						error("expected parameter");
						return false;
				}
				for (; version < inst->numversions; ++version) {
					if (isreg == inst->isreg[version][iparam]) break;
				}
				if (version == inst->numversions) {
					error("parameter type does not match any version of this instruction");
					return false;
				}
				if (iparam + 1 < inst->numparams && symbol != COMMA) {
					error("expected comma");
					return false;
				}
			}
			if (version < 0) {
				error("parameter types does not match any version of this instruction");
				return false;
			}
		} else getsymbol();
		if (symbol != TERMINATOR) {
			error("expected terminator");
			return false;
		}
		atom.symbol = INSTRUCTION;
		atom.opcode = inst->opcodebase + version;
		atomstack.push_back(atom);
		return true;
	}

	bool crpngen::expect_operand(bool orterminator) {
		switch (symbol) {
			case COMMA:
			case TERMINATOR:
				if (orterminator) return true;
				break;
			case NAME:
				atomstack.push_back(atom);
				getsymbol();
				return expect_operator();
			case NUMBER:
				atomstack.push_back(atom);
				getsymbol();
				return expect_operator();
			case OPERATOR:
				if (atom.op == LPAREN) {
					ops.push_back(atom.op);
					getsymbol();
					return expect_operand();
				}
				break;
			case REGISTER:
				error("register unexpected here");
				return false;
		}
		error("expected operand");
		return false;
	}

	bool crpngen::expect_operator() {
		switch (symbol) {
			case COMMA:
			case TERMINATOR:
				return true;
			case OPERATOR:
				if (OPS[atom.op].is_math) {
					while (ops.size()) {
						eoperator &back = ops.back();
						if (
						 OPS[back].is_math &&
						 (OPS[atom.op].is_left_assoc && (OPS[atom.op].precedence <= OPS[back].precedence))
						 ||
						 (!OPS[atom.op].is_left_assoc && (OPS[atom.op].precedence < OPS[back].precedence))
						) {
							satom newatom;
							newatom.symbol = OPERATOR;
							newatom.op = back;
							atomstack.push_back(newatom);
							ops.pop_back();
						} else break;
					}
					ops.push_back(atom.op);
					break;
				} else if (atom.op == RPAREN) {
					bool pe = false;
					while (ops.size()) {
						if (ops.back() == LPAREN) {
							pe = true;
							break;
						} else {
							atom.op = ops.back();
							atomstack.push_back(atom);
							ops.pop_back();
						}
					}
					if (!pe) {
						error("expected right parenthesis");
						return false;
					}
					ops.pop_back();
					getsymbol();
					return expect_operator();
				} else {
					if (OPS[atom.op].is_assign && atomstack.back().symbol != NAME) {
						error("can only assign to a name");
						return false;
					}
					ops.push_back(atom.op);
					break;
				}
			default:
				error("expected operator or terminator");
				return false;
		}
		getsymbol();
		return expect_operand();
	}

	crpngen::crpngen() {
		input = 0;
		symbol = ERR;
		nlcount = 1;
		colcount = 1;
		varcount = 0;
		instcount = 0;
		filtercount = 0;
		end = false;
	}

	crpngen::~crpngen() {}

	sstatement *crpngen::compact() {
		int size = atomstack.size();
		if (!size) return 0;
		char *err = "failed to allocate memory in nrpngen::crpngen::compact()";
		sstatement *statement = new sstatement;
		if (statement) {
			eatom *type = new eatom[size];
			if (type) {
				uatom *atom = new uatom[size];
				if (atom) {
					int i;
					vector<satom>::const_iterator iter;
					iter = atomstack.begin();
					for (i = 0; i < size; ++i, iter++) {
						switch (iter->symbol) {
							case INSTRUCTION:
								type[i] = INST;
								atom[i].inst = iter->inst;
								atom[i].inst >= 0xf0 ? ++filtercount : ++instcount;
								continue;
							case REGISTER:
								type[i] = REG;
								atom[i].reg = iter->reg;
								continue;
							case NAME: {
								type[i] = VAR;
								map<string, int>::const_iterator variter;
								variter = varmap.find(iter->name);
								if (variter == varmap.end()) {
									varmap[iter->name] = varcount;
									atom[i].ivar = varcount;
									++varcount;
								} else atom[i].ivar = varmap[iter->name];
							} continue;
							case NUMBER:
								type[i] = NUM;
								atom[i].num = iter->dub;
								continue;
							case OPERATOR:
								type[i] = OP;
								atom[i].op = iter->op;
								continue;
							default:
								err = "unexpected symbol in atomstack";
								break;
						}
						break;
					}
					if (i == size) {
						statement->size = size;
						statement->type = type;
						statement->atom = atom;
						atomstack.clear();
						ops.clear();
						return statement;
					}
					delete [] atom;
				}
				delete [] type;
			}
			delete statement;
		}
		cerr << err << endl;
		return 0;
	}

	void crpngen::readatom(satom &atom) {
		switch (atom.symbol) {
			case REGISTER: cout << "REGISTER: " << (int)atom.reg; break;
			case NAME: cout << "NAME: " << atom.name; break;
			case NUMBER: cout << "NUMBER: " << atom.dub; break;
			case OPERATOR: cout << "OPERATOR: "; readop(atom.op); break;
		}
		cout << endl;
	}

	void crpngen::reset() {
		varmap.clear();
		ops.clear();
		input = 0;
		atom.name.clear();
		symbol = ERR;
		nlcount = 0;
		colcount = 0;
		atomstack.clear();
		varcount = 0;
		instcount = 0;
		filtercount = 0;
		end = false;
	}

	void crpngen::set_input(istream *newinput) {
		input = newinput;	
	}

	void crpngen::set_instnames() {
		char *name = instnames[0];
		for (int i = 0; name; name = instnames[++i]) {
			instmap[name] = i;
		}
	}

	void crpngen::set_regnames(int count) {
		char name[3] = "r#";
		for (int i = 0; i < count; ++i) {
			name[1] = '0' + i;
			regmap[name] = i;
		}
	}

	bool crpngen::statement() {
		getsymbol();
		switch (symbol) {
			case INSTRUCTION:
				if (!finish_instruction()) return false;
				break;
			case OPERATOR:
				if (atom.op == ADD) {
					getsymbol();
					if (!expect_operand()) return false;
					if (symbol != TERMINATOR) {
						error("expected terminator");
						return false;
					}
					collapse_ops();
					atom.symbol = OPERATOR;
					atom.op = TIMEADD;
					atomstack.push_back(atom);
					break;
				} else if (atom.op != LPAREN) break;
			case NUMBER:
			case NAME:
				if (!expect_operand(true)) return false;
				switch (symbol) {
					case COMMA:
					case TERMINATOR:
						collapse_ops();
						if (symbol == COMMA) {
							getsymbol();
							if (!expect_operand()) return false;
							if (symbol != TERMINATOR) {
								error("expected terminator");
								return false;
							}
							collapse_ops();
							atom.symbol = OPERATOR;
							atom.op = TIME;
							atomstack.push_back(atom);
						}
						break;
					default:
						error("expected comma or terminator");
						return false;
				} break;
			case COMMA:
				getsymbol();
				if (!expect_operand()) return false;
				if (symbol != TERMINATOR) {
					error("expected terminator");
					return false;
				}
				collapse_ops();
				atom.symbol = OPERATOR;
				atom.op = TIMESHORT;
				atomstack.push_back(atom);
				break;
			case TERMINATOR:
				break;
			case END:
				end = true;
				return false;
			case ERR:
				return false;
			default:
				error("expected an instruction, operand, comma or terminator");
				return false;
		}
		return true;
	}
}