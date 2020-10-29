#!/bin/bash
# backup.sh
# Author: Barrett Noone
# Date: 9/16/20
# Description: 

if [ ! -d ../indexdir ] ; then
				mkdir ../indexdir
fi

if [ ! -d ../indexcomp ] ; then
				mkdir ../indexcomp
fi

make -f Makefile > /dev/null

echo "Creating a index file in ../indexdir"
../indexer/indexer_step6
echo "Running test to load from index file, then re-save"
../indexer/iotest_6
echo "checking diff on original file and new file"
DIFF=$(diff ../indexdir/1 ../indexdir2/1)
if [[ "$DIFF" == "" ]] ; then
    echo "No differences!"
else
    echo "Didn't match :("
fi
