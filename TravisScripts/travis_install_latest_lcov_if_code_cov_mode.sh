#!/bin/sh
set -eu

if [ "$CODE_COV_MODE" = "ON" ]; then
   export LCOV_ROOT="$HOME/lcov"
   mkdir -p "$LCOV_ROOT"
   wget https://github.com/linux-test-project/lcov/releases/download/v1.15/lcov-1.15.tar.gz --output-document="$LCOV_ROOT/lcov.tar.gz"
   tar xf "$LCOV_ROOT/lcov.tar.gz" --strip-components=1 -C $LCOV_ROOT
   export PATH="$LCOV_ROOT/bin:$PATH"
   which lcov
   lcov --version
fi
