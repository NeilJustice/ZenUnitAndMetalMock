#!/bin/bash
set -e

cmake -GNinja -DCMAKE_INSTALL_PREFIX=/usr/local
cmake --build . --target install
