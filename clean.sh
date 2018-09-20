#!/bin/bash

# sometimes, `cmake .` can't update makefile very well because these
# cache files exists, need delete them before updating makefile
rm -rf CMakeCache.txt
rm -rf CMakeFiles/