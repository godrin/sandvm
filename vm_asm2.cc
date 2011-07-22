#include "vm_asm.h"
#include "vm_ops.h"
#include "vm_memory.h"
#include "vm_tools.h"
#include "vm_arg.h"
#include "vm_log.h"
#include "vm_instruction.h"
#include "vm_encoding.h"

#include <iostream>
#include <map>

#define LOGLEVEL 1

namespace Asm2 {

class EofException {

};

class Lexer {
	std::istream &stream;

	std::string buffer;

public:

	enum Item {
		ENCLOSED_STRING, //0
		SYMBOL, // 1
		LABEL, // 2
		WHITESPACE, //3
		NEWLINE, // 4
		COMMA, // 5
		COMMAND, // 6
		MEOF, // 7
		NUMBER, // 8
		POINT, // 9
		DASH, // 10
		WORD, // 11
		REGISTER, // 12
		QUEUE, // 13
		COMMENT, // 14
		MODIFIER
	// 15
	// 14
	};

	Lexer(std::istream &p) :
			stream(p) {
	}

	char get() {
		char c;
		if (buffer.length() > 0) {
			c = buffer[0];
			buffer = buffer.substr(1, std::string::npos);
		} else if (!stream.eof()) {
			c = readChar();
		} else
			throw EofException();
		return c;
	}

	char lookaheadchar() {
		char c;
		if (buffer.length() > 0) {
			c = buffer[0];
		} else {
			c = readChar();
			buffer += c;
		}
		return c;
	}

	char readChar() {
		char c;
		stream.read(&c, 1);
		logger(LOGLEVEL) << "char:" << (int) c << " eof:" << stream.eof()
				<< vmlog::endl;
		return c;
	}

	bool eof() {
		return (stream.eof()); // && buffer.length() == 0); FAIL
	}

	bool isWhitespace(char c) {
		return c == ' ' || c == '\t';
	}
	bool isNumber(char c) {
		return c >= '0' && c <= '9';
	}
	bool isChar(char c) {
		return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
	}

	bool isRegister(const std::string &n) {
		if (n[0] != 'R')
			return false;
		for (size_t i = 1; i < n.length(); i++)
			if (!isNumber(n[i]))
				return false;
		return true;
	}
	bool isQueue(const std::string &n) {
		if (n[0] != 'Q')
			return false;
		for (size_t i = 1; i < n.length(); i++)
			if (!isNumber(n[i]))
				return false;
		return true;
	}

	std::pair<Item, std::string> next() {
		if (eof())
			return std::make_pair(MEOF, "");
		char la = lookaheadchar();
		if (la == ';') {
			std::string c = "";
			do {
				c += get();
			} while (lookaheadchar() != '\n' && lookaheadchar() != 0);
			return std::make_pair(COMMENT, c);
		} else if (la == '.') {
			get();
			la = lookaheadchar();
			if (la == 'a') {
				get();
				return std::make_pair(MODIFIER, "a");
			} else if (la == 'b') {
				get();
				return std::make_pair(MODIFIER, "b");
			} else if (la == 'w') {
				get();
				return std::make_pair(MODIFIER, "w");
			} else if (la == 'd') {
				get();
				return std::make_pair(MODIFIER, "d");
			}
		} else if (la == '\n') {
			get();
			return std::make_pair(NEWLINE, "*newline*");
		} else if (la == '*') {
			get();
			return std::make_pair(POINT, "*");
		} else if (la == ',') {
			get();
			return std::make_pair(COMMA, ",");
		} else if (la == '#') {
			get();
			return std::make_pair(DASH, "*");
		} else if (la == ' ' || la == '\t') {
			while (isWhitespace(lookaheadchar()))
				get();
			return std::make_pair(WHITESPACE, " ");
		} else if (isNumber(la)) {
			std::string n;
			while (isNumber(lookaheadchar()))
				n += get();
			return std::make_pair(NUMBER, n);
		} else if (la == ':') {
			std::string n;
			get();
			while (isNumber(lookaheadchar()) || isChar(lookaheadchar()))
				n += get();
			return std::make_pair(SYMBOL, n);
		} else if (isChar(la)) {
			std::string n;
			while (isNumber(lookaheadchar()) || isChar(lookaheadchar()))
				n += get();
			if (lookaheadchar() == ':') {
				get();
				return std::make_pair(LABEL, n);
			}
			VMOps op = getOp(n);

			if (op != INV) {
				return std::make_pair(COMMAND, n);
			}
			if (isRegister(n))
				return std::make_pair(REGISTER, n);
			if (isQueue(n))
				return std::make_pair(REGISTER, n);
			return std::make_pair(WORD, n);
		} else if (la == '\'' || la == '"') {
			get();
			std::string n;
			while (lookaheadchar() != la) {
				n += get();
			}
			get();
			return std::make_pair(ENCLOSED_STRING, n);
		} else if (la == 0) {
			get();
			return std::make_pair(WHITESPACE, "");
		} else {
			std::cerr << "Nothing found for la:" << la << " " << (int) la
					<< std::endl;
			throw new EofException();
		}
	}

};

class Arg {
public:
	size_t value;
	bool reg;
	bool direct;
	std::string label;
	bool used;

};

class Line {
public:
	std::string label;
	std::string data;
	VMOps op;
	Arg arg0, arg1;
	bool last;
	size_t lineNumber;
	std::string type;

	void toInstruction(VMInstruction *i) {
		VMType t = getType();
		i->setOp(op);
		i->setType(t);

		i->getArg0()->setDirect(arg0.direct);
		i->getArg0()->setRegister(arg0.reg);
		setValue(&arg0, i->getArg0(), t);

		i->getArg1()->setDirect(arg1.direct);
		i->getArg1()->setRegister(arg1.reg);
		setValue(&arg1, i->getArg1(), t);
	}

private:
	void setValue(Arg *arg, VMArg *vmarg, VMType t) {
		switch (t) {
		case BYTE:
			vmarg->set((Uint8) arg->value);
			break;
		case WORD:
			vmarg->set((Uint16) arg->value);
			break;
		case DWORD:
		case ADDRESS:
			vmarg->set((Uint32) arg->value);
			break;
		default:
			throw int();
		}
	}
	VMType getType() {
		VMType t;

		if (type == "a" || type == "d") {
			t = DWORD;
		} else if (type == "w") {
			t = WORD;
		} else {
			t = BYTE;
		}
		return t;
	}

};

class NuParser {
public:
	typedef ::Asm2::Lexer Lexer;
private:
	Lexer *lexer;
	VMMemory *memory;
	std::pair<Lexer::Item, std::string> current;
	size_t lineNumber;
public:

	NuParser(Lexer *l, VMMemory *pmemory) :
			lexer(l), memory(pmemory) {
		next();
		lineNumber = 1;
	}

	void readArg(Arg*arg) {
		if (current.first == Lexer::POINT) {
			arg->direct = false;
			next();
		} else {
			arg->direct = true;
		}

		if (current.first == Lexer::SYMBOL) {
			arg->label = current.second;
			arg->reg = false;
			arg->used = true;
			next();
		} else if (current.first == Lexer::REGISTER) {
			arg->reg = true;
			arg->value = atoi(
					current.second.substr(1, std::string::npos).c_str());
			arg->used = true;
			next();
		} else if (current.first == Lexer::NUMBER) {
			arg->reg = false;
			arg->value = atoi(current.second.c_str());
			arg->used = true;
			next();
		} else if (current.first == Lexer::ENCLOSED_STRING
				&& current.second.length() == 1) {
			arg->used = true;
			arg->reg = false;
			arg->value = current.second[0];
			next();
		} else if (current.first == Lexer::NEWLINE) {

		} else {
			logger(LOGLEVEL) << "Error at " << current.first << ":"
					<< current.second << vmlog::endl;
			throw int();
		}

	}

	Line getLine() {
		while (current.first == Lexer::NEWLINE) {
			next();
			lineNumber += 1;
		}

		Line l;
		l.op = INV;
		l.lineNumber = lineNumber;

		if (current.first == Lexer::LABEL) {
			l.label = current.second;
			next();
		}
// eat newlines
		while (current.first == Lexer::NEWLINE) {
			next();
			lineNumber += 1;
		}

		if (current.first == Lexer::MEOF) {
			l.last = true;
			return l;
		}

		if (current.first == Lexer::COMMAND) {
			l.op = getOp(current.second);
			logger(LOGLEVEL) << current.first << ":" << current.second
					<< vmlog::endl;
			next();
			logger(LOGLEVEL) << current.first << ":" << current.second
					<< vmlog::endl;

			if (current.first == Lexer::MODIFIER) {
				l.type = current.second;
				next();
			}

			readArg(&l.arg0);

			if (current.first == Lexer::COMMA) {
				next();
			}

			readArg(&l.arg1);

			if (current.first == Lexer::NEWLINE)
				next();
			else {
				logger(LOGLEVEL) << "Error at:" << current.first << ":"
						<< current.second << vmlog::endl;
				throw int();
			}
		} else if (current.first == Lexer::WORD) {
			if (toUpper(current.second) == "EQU") {
				next();
				if (current.first == Lexer::ENCLOSED_STRING) {
					l.data = current.second;
					next();
				} else {
					logger(LOGLEVEL) << "Error at:" << current.first << ":"
							<< current.second << vmlog::endl;
					throw int();
				}
			} else {
				logger(LOGLEVEL) << "Error at:" << current.first << ":"
						<< current.second << vmlog::endl;
				throw int();

			}

//FIXME ARGS
		} else if (current.first == Lexer::NEWLINE) {
			return l;
		} else {
			logger(LOGLEVEL) << "Error at:" << current.first << ":"
					<< current.second << " line:" << lineNumber << vmlog::endl;
			throw int();
		}

		return l;
	}

private:
	void next() {
		do {
			current = lexer->next();
			logger(LOGLEVEL) << "NEXT:" << current.first << ":"
					<< current.second << vmlog::endl;
		} while (current.first == Lexer::WHITESPACE
				|| current.first == Lexer::COMMENT);

	}
};

void parse(std::istream &stream, VMMemory *memory, size_t start,
		VMEncoding *encoder) {
	Lexer lexer(stream);

	NuParser p(&lexer, memory);
	Line l;

	std::vector<Line> lines;
	std::map<std::string, size_t> refs;
	size_t pos = start;
	size_t cur = start;
	VMInstruction instruction;

	while (!(l = p.getLine()).last) {
		lines.push_back(l);
		if (l.label.length() > 0)
			refs.insert(std::make_pair(l.label, pos));
		if (l.data.length() > 0) {
			pos += l.data.length();
		} else {
			l.toInstruction(&instruction);
			pos += encoder->encode(0, 0, &instruction);
		}
	}
	if (l.label.length() > 0)
		refs.insert(std::make_pair(l.label, pos));

	for (std::vector<Line>::iterator i = lines.begin(); i != lines.end(); i++) {
		l = *i;
		if (l.data.length() > 0) {
			for (size_t x = 0; x < l.data.length(); x++) {
				memory->set(cur++, l.data[x]);
			}
		} else {

			if (l.arg0.label.length() > 0) {
				logger(LOGLEVEL) << "arg0 label:" << l.arg0.label << " set to "
						<< refs[l.arg0.label] << vmlog::endl;
				l.arg0.value = refs[l.arg0.label];
			}
			if (l.arg1.label.length() > 0) {
				logger(LOGLEVEL) << "arg1 label:" << l.arg1.label << " set to "
						<< refs[l.arg1.label] << vmlog::endl;
				l.arg1.value = refs[l.arg1.label];
			}

			l.toInstruction(&instruction);
			logger(LOGLEVEL) << "arg0:" << l.arg0.value << " arg1:"
					<< l.arg1.value << vmlog::endl;
			cur += encoder->encode(memory, cur, &instruction);
		}

	}

}
}

