#!/bin/bash
set -e

CXX=/usr/local/bin/clang++ cmake -H. -BDebug -GNinja -DCMAKE_BUILD_TYPE=Debug -DClangTidyMode=ON
(cd Debug; time ninja clang-tidy)

CXX=/usr/local/bin/clang++ cmake -HZenUnitHelloWorld -BDebug -GNinja -DCMAKE_BUILD_TYPE=Debug -DClangTidyMode=ON
(cd ZenUnitHelloWOrld/Debug; time ninja clang-tidy)
