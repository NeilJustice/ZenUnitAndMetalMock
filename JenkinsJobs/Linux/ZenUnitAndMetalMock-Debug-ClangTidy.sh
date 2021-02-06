#!/bin/bash
set -ev
CXX=/usr/bin/clang++ cmake -H. -BDebug -GNinja -DCMAKE_BUILD_TYPE=Debug -DClangTidyMode=ON
(cd Debug; time ninja clang-tidy)
