cmake_minimum_required(VERSION 3.15)
project(JanGeschenk)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
SET(CMAKE_CXX_FLAGS "-Wall -Werror -O3")
set(EXECUTABLE_OUTPUT_PATH ../bin)

add_executable(basic_compile main.cpp)
target_link_libraries(basic_compile PUBLIC ${CONAN_LIBS})

install(FILES Webconsole.hpp Webgame.hpp DESTINATION ${CMAKE_INSTALL_PREFIX}/include/JanGeschenk)
