#!/bin/bash

set -e

make clean
make

./devpkg -S
./devpkg -L

./devpkg -F http://example.com/package.tar.gz || true


