cmake_minimum_required(VERSION 2.6)
project(CMAKEDEMO)
  set(CMAKE_BUILD_TYPE "Debug")

include_directories(${PROJECT_BINARY_DIR}/api ${PROJECT_BINARY_DIR})

set(LIB_SRC vm_memory.cc vm_instruction.cc 
  vm_sim.cc vm_thread.cc vm_arg.cc vm_threads.cc
  vm_types.cc vm_vm.cc vm_queues.cc vm_stack.cc
  vm_ops.cc vm_asm.cc vm_tools.cc vm_encoding.cc 
  vm_log.cc vm_config.cc vm_pipeend.cc vm_pipe.cc vm_registers.cc)
  
  set(API_SRC api/vm_api.cc api/vm_api_file.cc)

#add_executable(vm vm.cc ${LIB_SRC})
add_executable(vm_run vm_run.cc ${LIB_SRC} ${API_SRC})

add_executable(vm_type_sizes vm_type_sizes.cc)

add_executable(vm_api_test api/vm_api_test.cc ${API_SRC})