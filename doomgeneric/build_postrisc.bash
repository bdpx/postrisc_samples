#!/usr/bin/env bash

# https://github.com/ozkl/doomgeneric
# git@github.com:ozkl/doomgeneric.git

# git remote add upstream git@github.com:ozkl/doomgeneric.git
# git remote -v
# git fetch upstream

rm -rf build

make -f Makefile.postrisc -j8
