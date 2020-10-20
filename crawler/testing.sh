#!/bin/bash

make

mkdir ../pagedir

countfiles(){
    x = 0
    pushd ../pagedir
    for f in *; do
        x=$x+1
    done
    echo "$x pages saved in ../pagedir"
    popd
}

echo "Test 1: run with invalid number of arguments"
./crawler_final https://thayer.github.io/engs50/ ../pagedir 1 blah

echo "Test 2: run with invalid depth"
./crawler_final https://thayer.github.io/engs50/ ../pagedir -4

echo "Test 3: run with invalid seed url"
./crawler_final bad_url ../pagedir

echo "Test 4: run with directory that doesn't exist"
./crawler_final https://thayer.github.io/engs50/ ../baddir 1

echo "Test 5: run with valid arguments at depth 1"
./crawler_final https://thayer.github.io/engs50/ ../pagedir 1 >&/dev/null
countfiles

make

echo "Test 6: run with valid arguments at depth 2"
./crawler_final https://thayer.github.io/engs50/ ../pagedir 2 >&/dev/null
countfiles

make

echo "Test 7: run with directory that is unwritable"
chmod -w ../pagedir
./crawler_final https://thayer.github.io/engs50/ ../pagedir 2
chmod +w ../pagedir

echo "Test 8: run valgrind with depth 1"
valgrind --leak-check=full crawler_final https://thayer.github.io/engs50/ ../test 1


