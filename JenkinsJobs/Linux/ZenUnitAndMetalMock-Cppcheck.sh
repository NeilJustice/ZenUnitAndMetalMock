#!/bin/bash
set -v

cores=$(grep -c ^processor /proc/cpuinfo)
cppcheck \
   --enable=all \
   --cppcheck-build-dir=Cppcheck \
   --suppressions-list=CppcheckSuppressions.txt \
   -D__linux__ \
   -DTEST \
   -DTHEN_RUN_TEMPLATE_TESTS \
   -DCOMMA \
   -DTEST \
   -DTESTS \
   -DAFACT \
   -DFACTS \
   -DTEST1X1 \
   -DTEST2X2 \
   -DTEST3X3 \
   -DTEST4X4 \
   -DTEST5X5 \
   -DTEST6X6 \
   -DTEST7X7 \
   -DTEST8X8 \
   -DTEST9X9 \
   -DTEST10X10 \
   -DMETALMOCK_VOID0_FREE \
   -DMETALMOCK_VOID1_FREE \
   -DMETALMOCK_VOID2_FREE \
   -DMETALMOCK_NONVOID0_STATIC \
   -DMETALMOCK_NONVOID1_FREE \
   -DMETALMOCK_NONVOID1_STATIC \
   -DMETALMOCK_NONVOID3_CONST \
   -I /usr/include/c++/v1 \
   -I ZenUnitTestUtils \
   -I . \
   -j "$cores" \
   --output-file=cppcheck_results.txt \
   --error-exitcode=1 \
   .
if [ $? = 1 ]; then
   echo "Error: Cppcheck failed with exit code 1"
   echo "cppcheck_results.txt:"
   cat cppcheck_results.txt
   exit 1
fi
