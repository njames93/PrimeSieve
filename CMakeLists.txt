cmake_minimum_required(VERSION 3.13.4)
project(Primes)

set(CMAKE_CXX_STANDARD 20)

option(USE_HOST_ARCH "Emit code optimised for the host architecture" OFF)

if(USE_HOST_ARCH)
  include(CheckCXXCompilerFlag)
  check_cxx_compiler_flag("-march=native" COMPILER_SUPPORTS_MARCH_NATIVE)
  if(COMPILER_SUPPORTS_MARCH_NATIVE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
  endif()
endif()

add_library(PrimeValidation Validation.cpp)

add_executable(Daves Dave.cpp)
target_link_libraries(Daves PrimeValidation)

add_executable(AdvBitManip AdvBitManip.cpp)
target_link_libraries(AdvBitManip PrimeValidation)
