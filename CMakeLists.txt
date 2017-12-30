cmake_minimum_required(VERSION 3.9)
project(tt1_information_retrieval)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if (MSVC_VERSION GREATER_EQUAL "1900")
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
    if (_cpp_latest_flag_supported)
        add_compile_options("/std:c++latest")
    endif()
endif()

if (DEFINED ENV{TRAVIS})
    include(CodeCoverage)
    setup_target_for_coverage(${PROJECT_NAME}_coverage tests coverage)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -pthread -g -O0 -fprofile-arcs -ftest-coverage")
    set(CMAKE_BUILD_TYPE "DEBUG")
endif()

set(SOURCE_FILES database.h database.cpp tokenizer.h tokenizer.cpp fileaccess.h fileaccess.cpp)
add_executable(tt1_information_retrieval main.cpp 3rdparty/CLI11.hpp ${SOURCE_FILES})

set(TEST_FILES 3rdparty/catch.h tst_database.cpp tst_main.cpp tst_tokenizer.cpp tst_integration.cpp test_helper.cpp test_helper.h)
add_executable(tst_tt1_information_retrieval ${SOURCE_FILES} ${TEST_FILES})

if(CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(tt1_information_retrieval -lstdc++fs)
    target_link_libraries(tst_tt1_information_retrieval -lstdc++fs)
endif()

if(DEFINED ENV{CI})
    set(TEST_OPTIONS -r junit -o xunit-results.xml)
endif()

enable_testing()
add_test(NAME tst_tt1_information_retrieval COMMAND tst_tt1_information_retrieval ${TEST_OPTIONS})