cmake_minimum_required(VERSION 3.10)

project(other)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

file(MAKE_DIRECTORY out)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/)

list(APPEND MAIN_FILE_LOCATION .)

file(GLOB MAIN_FILES ${MAIN_FILE_LOCATION}/*.cpp)
foreach (MAIN ${MAIN_FILES})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" NAME ${MAIN})
    add_executable (${NAME} ${MAIN})
endforeach ()