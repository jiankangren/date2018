cmake_minimum_required(VERSION 3.3)
project("TOOLNUMBERTWO" VERSION 0.1 LANGUAGES C CXX)

# Requirements
## Require Include-What-You-Use
set(IWYU OFF CACHE BOOL "If enable the include-what-you-use program")
if (IWYU)
  set(IWYU_PATH CACHE FILEPATH "Path to include-what-you-use program")
  message(STATUS "Searching for IWYU ... ")
  find_program(iwyu_path NAMES include-what-you-use iwyu)
  if(NOT iwyu_path)
    message(FATAL_ERROR "Could not find the program include-what-you-use."
                         "Either disable this requirement with -DIWYU:BOOL=OFF"
                         "or specify the program path with -DIWYU_PATH:FILEPATH=/path/to/iwyu"
            )
  endif(NOT iwyu_path)
  message(STATUS "Searching for IWYU ... FOUND: ${iwyu_path}")
  # Use IWYU
  set(CMAKE_C_INCLUDE_WHAT_YOU_USE ${iwyu_path})
  set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif(IWYU)

# Require C++11 features
set(CMAKE_CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wfatal-errors -Wwrite-strings")
set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

# set Paradiseo Module Path
LIST(APPEND CMAKE_MODULE_PATH "/usr/local/share/paradiseo/module/") 
# Required packages
# Require LLVM and Clang
find_package(LLVM 3.9.1 REQUIRED CONFIG)
# Require Paradiseo 2.0
find_package(Paradiseo COMPONENTS moeo eoutils eo)

# Require Pthreads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
# Require ZLIB
find_package(ZLIB REQUIRED)

message(STATUS "Found ZLIB ${ZLIB_VERSION_STRING}")
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
message(STATUS "Added LLVM include directories: ${LLVM_INCLUDE_DIRS}")
message(STATUS "Added LLVM definitions: ${LLVM_DEFINITIONS}")
message(STATUS "Added Paradiseo include directory: ${PARADISEO_INCLUDE_DIR}")

# Paradiseo Include Directory 
include_directories(${PARADISEO_INCLUDE_DIR})

# Add includes and definitions of LLVM
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Find the libraries that correspond to the LLVM/Clang components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs all analysis asmparser asmprinter bitreader bitwriter bpf bpfasmprinter bpfcodegen bpfdesc bpfinfo codegen core coverage debuginfocodeview debuginfodwarf debuginfopdb engine executionengine globalisel hexagon hexagonasmparser hexagoncodegen hexagondesc hexagondisassembler hexagoninfo instcombine instrumentation interpreter ipo irreader libdriver lineeditor linker lto mc mcdisassembler mcjit mcparser mirparser native nativecodegen objcarcopts object objectyaml option orcjit passes profiledata runtimedyld scalaropts selectiondag support symbolize systemz systemzasmparser systemzasmprinter systemzcodegen systemzdesc systemzdisassembler systemzinfo tablegen target transformutils vectorize x86 x86asmparser x86asmprinter x86codegen x86desc x86disassembler x86info x86utils xcore xcoreasmprinter xcorecodegen xcoredesc xcoredisassembler xcoreinfo)



list(APPEND clang_libs
     clangToolingCore
     clangFormat
     clangAST
     clangAnalysis
     clangBasic
     clangDriver
     clangEdit
     clangFrontend
     clangFrontendTool
     clangLex
     clangParse
     clangSema
     clangEdit
     clangASTMatchers
     clangRewrite
     clangRewriteFrontend
     clangStaticAnalyzerFrontend
     clangStaticAnalyzerCheckers
     clangStaticAnalyzerCore
     clangSerialization
     clangTooling
     clangCodeGen
     )

list(APPEND required_libs ${clang_libs} ${llvm_libs})

# Check on required libraries
# - LLVM/Clang Static Libraries
message(STATUS "Checking LLVM/Clang libraries: ${required_libs}")

set(LLVM_LIBRARY_DIR "/usr/lib/" CACHE STRING "Library search path for LLVM/Clang")
message(STATUS "Search path: LLVM_LIBRARY_DIR = ${LLVM_LIBRARY_DIR}")

set(required_libs_paths)
foreach (lib ${required_libs})
  find_library(required_lib_path ${lib} ${LLVM_LIBRARY_DIR})

  if (${required_lib_path} STREQUAL required_lib_path-NOTFOUND)
    message(FATAL_ERROR "The library ${lib} was not found in ${LLVM_LIBRARY_DIR}\nProvide a LLVM_LIBRARY_DIR: -DLLVM_LIBRARY_DIR:STRING=<library_path>.")
  endif()

  message(STATUS "Found library: ${required_lib_path}")
  list(APPEND required_libs_paths ${required_lib_path})
  unset(required_lib_path CACHE)
endforeach()


# - Others libraries
list(APPEND other_libs ffi edit ncurses dl m)
message(STATUS "Checking additional libraries: ${other_libs}")
foreach (lib ${other_libs})
  find_library(required_lib_path ${lib})

  if (${required_lib_path} STREQUAL required_lib_path-NOTFOUND)
    message(FATAL_ERROR "The library ${lib} was not found.")
  endif()
  message(STATUS "Found library: ${required_lib_path}")
  unset(required_lib_path CACHE)
endforeach()

###############################################################################
# Doxyen Support
## Search for Doxygen Package
find_package(Doxygen)

## In case has been found
if(DOXYGEN_FOUND)
  message(STATUS "Found Doxygen. It is available 'make doc' to generate the documentation")
  configure_file(${CMAKE_SOURCE_DIR}/src/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(doc
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/doc/doxygen
  COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)
###############################################################################

# Checks completed. Add sources/libraries/executables
# Add sources subdirectory
add_subdirectory(${CMAKE_SOURCE_DIR}/src)

# Targer: toolnumbertwo
add_executable(toolnumbertwo src/main.cpp)
# Includes
target_include_directories(toolnumbertwo
                           PRIVATE ${CMAKE_SOURCE_DIR}/include
                           )


# Link Libraries
target_link_libraries(toolnumbertwo
                      ${required_libs_paths}
                      ${PARADISEO_LIBRARIES}
                      )

# Link Libraries
target_link_libraries(toolnumbertwo
                      core exec_engine_helper tool plugins log 
                      ${PARADISEO_LIBRARIES}
                      )

## Relink to resolve circular dependencies
target_link_libraries(toolnumbertwo
                      ${required_libs_paths}
                      Threads::Threads
                      z
                      ffi
                      edit
                      ncurses
                      dl
                      m
                      )

install(TARGETS toolnumbertwo
        RUNTIME DESTINATION /usr/local/bin
        LIBRARY DESTINATION /usr/local/lib
        ARCHIVE DESTINATION /usr/local/lib 
)
