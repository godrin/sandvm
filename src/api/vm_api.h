#ifndef VM_API_H
#define VM_API_H

#include <string>
#include <list>
#include <iostream>

#include "vm_types.h"

class VMFct {
public:
	virtual std::string name()=0;
	virtual std::string call(std::string instr, size_t &pos)=0;

};

template<class T> std::string marshal(T t);
template<class T> T unmarshal(const std::string &s, size_t &pos);

template<>
std::string unmarshal(const std::string &s, size_t &pos);
template<>
Uint32 unmarshal(const std::string &s, size_t &pos);
template<>
std::string marshal(Uint32 i);
template<>
std::string marshal(std::string x);

class VMApiModule;
class VMVm;
class VMApi;

class VMApiModule {
public:
	virtual void init(VMApi *api)=0;
	virtual std::string getName()=0;

};

template<class X, class R, class P0, class P1, class P2>
class VMFct3: public VMFct {
	typedef R(X::*F)(P0, P1, P2);

	F fct;
	X *module;
	std::string methodName;
public:
	VMFct3(X *m, std::string mname, F &f) :
			fct(f), module(m), methodName(mname) {
	}

	std::string call(std::string instr, size_t &pos) {
		P0 a = unmarshal<P0>(instr, pos);
		P1 b = unmarshal<P1>(instr, pos);
		P2 c = unmarshal<P2>(instr, pos);
		R r = (module->*fct)(a, b, c);
		return marshal<R>(r);
	}
	std::string name() {
		return module->getName() + "." + methodName;
	}
};

class VMApi {
	std::list<VMFct*> fcts;
	VMVm *vm;

public:
	VMApi(VMVm *pvm) :
			vm(pvm) {

	}

	template<class X, class R, class P0, class P1, class P2>
	void reg(X *m, std::string methodName, R(X::*f)(P0, P1, P2)) {
		fcts.push_back(new VMFct3<X, R, P0, P1, P2>(m, methodName, f));
	}

	void call(std::string x) {
		size_t pos = 0;

		std::string name = unmarshal<std::string>(x, pos);
		for (std::list<VMFct*>::iterator i = fcts.begin(); i != fcts.end();
				i++) {
			VMFct *f = *i;
			if (f->name() == name) {
				std::cout << "FOUND:" << name << std::endl;
				std::string out = f->call(x, pos);
				std::cout << "out:" << out << std::endl;

			}
		}
	}

	template<class P0, class P1, class P2>
	void write(std::string module, std::string methodName, P0 p0, P1 p1,
			P2 p2) {
		call(
				marshal(module + "." + methodName) + marshal(p0) + marshal(p1)
						+ marshal(p2));
	}

};

#endif
