#!/bin/bash
echo "testing module with 1 thread"
echo "========================================================================"
echo "test2: tests all functions in single thread"
valgrind test2
echo "========================================================================"
echo "testing modules with 2 threads: lhash apply has been applied to all tests to print results"
echo "========================================================================"
echo "ctest3: search for existing element"
valgrind ctest3
echo "========================================================================"
echo "ctest4: search for non-existing element"
valgrind ctest4
echo "========================================================================"
echo "concurrent2: adding three elements"
valgrind concurrent2
echo "========================================================================"
echo "ctest5: opening and closing hashtable"
valgrind ctest5
echo "========================================================================"
echo "ctest6: removing existing element"
valgrind ctest6
echo "========================================================================"
echo "ctest7: removing non-existing element"
valgrind ctest7
echo "========================================================================"
echo "ctest9: functions for a null hashtable"
valgrind ctest9
echo "--done"
