#!/bin/bash
set -ev

export CXX=/usr/bin/clang++
cmake -H. -BRelWithDebInfo -GNinja -DCMAKE_BUILD_TYPE=RelWithDebInfo -DClangTidyMode=ON
(cd RelWithDebInfo; time ninja clang-tidy)
