#!/bin/bash

set -e

echo "Running unit tests"

for test in tests/*_tests
do 
	if [ -x "$test" ];then
		echo "$test"
		"$test"
	fi
done

echo "All tests passed"
