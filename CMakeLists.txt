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

add_library(options INTERFACE)
include(cmake/Sanitizers.cmake)
enable_sanitizers(options)

if(MSVC)
  string(REGEX REPLACE "( |^)/EHs( |$)" " " NEW_FLAGS ${CMAKE_CXX_FLAGS})
  string(REGEX REPLACE "( |^)/EHc( |$)" " " NEW_FLAGS ${NEW_FLAGS})
  string(REGEX REPLACE "( |^)/EHsc( |$)" " " NEW_FLAGS ${NEW_FLAGS})
  string(REGEX REPLACE "( |^)/GR( |$)" " " NEW_FLAGS ${NEW_FLAGS})
  set(CMAKE_CXX_FLAGS "${NEW_FLAGS} /D _HAS_EXCEPTIONS=0 /EHs-c- /GR-")
else()
  string(REGEX REPLACE "( |^)-fexceptions( |$)" " " NEW_FLAGS
                       "${CMAKE_CXX_FLAGS}")
  string(REGEX REPLACE "( |^)-frtti( |$)" " " NEW_FLAGS "${NEW_FLAGS}")
  set(CMAKE_CXX_FLAGS "${NEW_FLAGS} -fno-exceptions -fno-rtti -Wall -Wextra")
endif()

add_library(PrimeValidation Validation.cpp)

add_executable(Daves Dave.cpp)
target_link_libraries(Daves PrimeValidation options)

add_executable(FFSTwos FFSTwos.cpp)
target_link_libraries(FFSTwos PrimeValidation options)

add_executable(FFSThrees FFSThrees.cpp)
target_link_libraries(FFSThrees PrimeValidation options)
