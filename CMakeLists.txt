cmake_minimum_required(VERSION 3.01)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -g -pg")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O2 ")

set(SOURCE_FILES
	Path.cpp)

add_executable(test1 tests/test1.cpp ${SOURCE_FILES})