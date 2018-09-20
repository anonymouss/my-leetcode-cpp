cmake_minimum_required (VERSION 3.12)

project (my-leetcode-way)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSION OFF)

file(MAKE_DIRECTORY bin)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/)

file (GLOB files src/*.cpp)
foreach (file ${files})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
    add_executable (${exe} ${file})
    message (\ \ \ \ --\ src/${exe}.cpp\ will\ be\ compiled\ to\ bin/${exe})
endforeach ()