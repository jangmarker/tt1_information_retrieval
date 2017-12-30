cmake_minimum_required(VERSION 3.9)
project(tt1_information_retrieval)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES database.h database.cpp tokenizer.h tokenizer.cpp fileaccess.h fileaccess.cpp)
add_executable(tt1_information_retrieval main.cpp 3rdparty/CLI11.hpp ${SOURCE_FILES})

set(TEST_FILES 3rdparty/catch.h tst_database.cpp tst_main.cpp tst_tokenizer.cpp tst_integration.cpp test_helper.cpp test_helper.h)
add_executable(tst_tt1_information_retrieval ${SOURCE_FILES} ${TEST_FILES})

if(CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(tt1_information_retrieval -lstdc++fs)
    target_link_libraries(tst_tt1_information_retrieval -lstdc++fs)
endif()