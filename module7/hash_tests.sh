#!/bin/bash
echo "testing module with 1 thread"
echo "========================================================================"
echo "test2: testing all functions with single thread"
test2
echo "========================================================================"
echo "testing modules with 2 threads: lhash apply has been applied to all tests to print results"
echo "========================================================================"
echo "ctest3: search for existing element"
ctest3
echo "========================================================================"
echo "ctest4: search for non-existing element"
ctest4
echo "========================================================================"
echo "concurrent2: adding three elements"
concurrent2
echo "========================================================================"
echo "ctest5: opening and closing hashtable"
ctest5
echo "========================================================================"
echo "ctest6: removing existing element"
ctest6
echo "========================================================================"
echo "ctest7: removing non-existing element"
ctest7
echo "========================================================================"
echo "ctest9: functions for a null hashtable"
ctest9
echo "--done"
