cmake_minimum_required(VERSION 2.6)
project(CMAKEDEMO)
set(LIB_SRC vm_memory.cc vm_regs.cc vm_instruction.cc vm_sim.cc vm_thread.cc vm_arg.cc vm_threads.cc vm_types.cc vm_vm.cc vm_queues.cc vm_loader.cc vm_stack.cc vm_ops.cc)

add_executable(vm vm.cc ${LIB_SRC})
add_executable(vm_run vm_run.cc ${LIB_SRC})
