#include "vm_instruction.h"

VMArg *VMInstruction::getArg0() {
	return &arg0;
}
VMArg *VMInstruction::getArg1() {
	return &arg1;
}

VMOps VMInstruction::getOp() {
	return op;
}

void VMInstruction::set(VMMemory *memory, size_t ip) {
	VMMemoryData data = memory->get(ip);

#ifdef UINT32_USED
	if (data.get(0) <= NOP) {
		op = (VMOps) data.get(0);
	}
	Uint8 flags = data.get(1);
	Uint8 aValue = data.get(2);
	Uint8 bValue = data.get(3);
#else
	if (data.asSizeT() <= NOP) {
		op = (VMOps) data.asSizeT();
	}
	size_t flags = memory->get(ip + 1).asSizeT();
	size_t aValue = memory->get(ip + 2).asSizeT();
	size_t bValue = memory->get(ip + 3).asSizeT();

#endif

	arg0.setDirect(flags & 1);
	arg0.setRegister(flags & 2);
	arg1.setDirect(flags & 4);
	arg1.setRegister(flags & 8);

	std::cout << "READ ip:"<<ip<<" a.direct:" << (int) arg0.isDirect() << " a.reg:"
			<< (int) arg0.isRegister() << " b.direct:" << (int) arg1.isDirect()
			<< " b.reg:" << (int) arg1.isRegister() << " flag:"
			<< flags << std::endl;


	arg0.setValue(aValue);
	arg1.setValue(bValue);
}

VMInstruction ins(VMOps op, VMArg a) {
	VMInstruction i;
	i.setOp(op);
	i.setArg0(a);
	return i;
}
VMInstruction ins(VMOps op, VMArg a, VMArg b) {
	VMInstruction i;
	i.setOp(op);
	i.setArg0(a);
	i.setArg1(b);
	return i;

}

void VMInstruction::setOp(VMOps p) {
	op = p;
}
void VMInstruction::setArg0(VMArg a) {
	arg0 = a;
}
void VMInstruction::setArg1(VMArg b) {
	arg1 = b;
}

void VMInstruction::putAt(VMMemory *memory, size_t pos) {

	memory->set(pos++, op);

	VMMemoryData flags;
	flags.setBit(0, arg0.isDirect());
	flags.setBit(1, arg0.isRegister());
	flags.setBit(2, arg1.isDirect());
	flags.setBit(3, arg1.isRegister());
	std::cout << "a.direct ip:"<<(pos-1)<<" :" << (int) arg0.isDirect() << " a.reg:"
			<< (int) arg0.isRegister() << " b.direct:" << (int) arg1.isDirect()
			<< " b.reg:" << (int) arg1.isRegister() << " flag:"
			<< flags.asSizeT() << std::endl;

	memory->set(pos++, flags);
	memory->set(pos++, arg0.getValue());
	memory->set(pos++, arg1.getValue());

}
