cmake_minimum_required(VERSION 3.3)
project(evil_hangman)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_CXX)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.9.3")
        message(FATAL_ERROR "${CMAKE_CXX_COMPILER_VERSION}")
    endif()
endif()
set(SOURCE_FILES main.cpp)
set(SOURCE_FILES ${SOURCE_FILES} EvilHangman.cpp EvilHangman.hpp EvilWord.cpp EvilWord.hpp)
add_executable(evil_hangman ${SOURCE_FILES})