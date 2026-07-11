cmake_minimum_required(VERSION 3.23)

project(CppPlayground LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_program(CLANG_TIDY_EXE NAMES clang-tidy)

if(CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY
        ${CLANG_TIDY_EXE}
        -checks=clang-analyzer-*,bugprone-*,cppcoreguidelines-*,modernize-*,performance-*,readability-*,-readability-identifier-length
    )
endif()

add_executable(cpp-playground)

target_sources(cpp-playground
  PRIVATE
    src/main.cpp
)

target_compile_options(cpp-playground PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wconversion
    -Wnull-dereference
    -Wdangling
    #-Wlifetime
    -Wno-c++98-compat
    -Wno-c++98-compat-pedantic
    -Wno-padded
)
