#ifndef VM_REGS_H
#define VM_REGS_H

#include <vector>

template<class T>
class VMRegisters {
  size_t count;
  T *content;

	public:
  VMRegisters(size_t pCount);
  ~VMRegisters();

  T get(size_t index);
  void set(size_t index,const T &value);
  VMRegisters *clone();
};


#endif

