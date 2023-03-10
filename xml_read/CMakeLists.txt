cmake_minimum_required(VERSION 2.6)
 
project(xml_read)
set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin)

include_directories( ./)
set(SRC_LIST main.cpp MoonsSfwFileLoader.cpp tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp)


add_executable(result ${SRC_LIST})