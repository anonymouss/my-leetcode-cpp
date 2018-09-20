# my-leetcode-cpp

----
my leetcode solutions in C++

Required:
CMake ( > 3.12), C++11 (gcc > 4.8)

Usage:

- run `./clean.sh` before generating or updating makefile from CMake, because last CMake cache may block updating of some changes.
- run `cmake .` to generate or update makefile using CMake.
- run `make` to compile all source codes in `src/`, the executable binary files will be stored in `bin/`
- `cd` to `bin/` and verify manually
- run `make clean` to delete all binary files in `bin/`