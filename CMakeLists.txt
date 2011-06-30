cmake_minimum_required(VERSION 2.6)
project(CMAKEDEMO)
add_executable(vm vm_memory.cc vm.cc vm_regs.cc
 vm_instruction.cc vm_sim.cc vm_thread.cc vm_arg.cc vm_threads.cc vm_types.cc vm_vm.cc
 vm_queues.cc
 )
