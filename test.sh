#!/bin/bash

set -e

DBFILE="test.db"

echo "=== Testing Database Program ==="

rm -f $DBFILE

echo "1. Creating database..."
./ex17 $DBFILE c

echo "2.Adding records..."
./ex17 $DBFILE s 1 Zed zed@zedshow.com
./ex17 $DBFILE s 2 Frank frank@zedshow.com
./ex17 $DBFILE s 3 joe joe@zedshow.com

echo "3. Getting record 2..."
./ex17 $DBFILE g 2

echo "4. Listing all records..."
./ex17 $DBFILE l

echo "Deleting record 3..."
./ex17 $DBFILE d 3

echo "Listing after deletion..."
./ex17 $DBFILE l

echo "Testing error handling..."
if ./ex17 $DBFILE g 999; then
	echo "ERROR: Should have failed1"
	exit 1
fi

echo "=== All tests passed! =="
