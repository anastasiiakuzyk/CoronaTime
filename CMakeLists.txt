cmake_minimum_required(VERSION 3.14)
project(CoronaTime)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Source.cpp Enemy.cpp FontActions.cpp Map.cpp Player.cpp sources)
add_executable(CoronaTime ${SOURCE_FILES})
#include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(CoronaTime sfml-system sfml-window sfml-graphics sfml-audio sfml-network)