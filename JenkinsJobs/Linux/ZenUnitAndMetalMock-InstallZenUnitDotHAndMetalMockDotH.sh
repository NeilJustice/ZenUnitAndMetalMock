#!/bin/bash
set -ev

cmake . -GNinja -DCMAKE_INSTALL_PREFIX=/usr/local
cmake --build . --target install
