#!/usr/bin/env bash

set -e

g++ -std=c++17 -Wall -Wextra -Wpedantic src/*.cpp -Iinclude -o boolean_retrieval_engine

output=$(printf 'index AND retrieval\nexit\n' | ./boolean_retrieval_engine)

grep -q 'D1 (doc1.txt)' <<< "$output"
grep -q 'D2 (doc2.txt)' <<< "$output"

echo "Smoke test passed."

