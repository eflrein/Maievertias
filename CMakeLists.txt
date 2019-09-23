cmake_minimum_required(VERSION 3.01)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -g -pg")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O2 ")

include_directories(.)

set(SOURCE_FILES
		Path.cpp
		#File.cpp
		)

add_executable(test-path tests/test-path.cpp ${SOURCE_FILES})