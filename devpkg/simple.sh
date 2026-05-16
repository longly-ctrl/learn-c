#!/bin/bash

set -e

make clean
make

./devpkg -S
./devpkg -L

