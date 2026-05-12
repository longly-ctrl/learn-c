#!/usr/bin/env bash
set -e

make

echo "look around"
printf "l\n" | ./ex19

echo "valid movement"
printf "s\n" | ./ex19

echo "invalid movement"
printf "n\n" | ./ex19

echo "go to attack"
printf "n\nw\na\na\na\na\n" | ./ex19

