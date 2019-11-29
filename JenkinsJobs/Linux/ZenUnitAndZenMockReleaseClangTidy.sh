#!/bin/bash
set -e
CXX=/usr/bin/clang++ cmake -H. -BRelease -GNinja -DCMAKE_BUILD_TYPE=Release -DClangTidyMode=ON
i(cd Release; time ninja clang-tidy)

