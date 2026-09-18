#!/usr/bin/env bash

set -e

g++ -std=c++17 -Wall -Wextra -Wpedantic src/*.cpp -Iinclude -o boolean_retrieval_engine

output=$(printf 'index OR data AND missing\nexit\n' | ./boolean_retrieval_engine)

grep -q 'D1 (doc1.txt)' <<< "$output"
if grep -q 'D3 (doc3.txt)' <<< "$output"; then
    echo "AND must be evaluated before OR."
    exit 1
fi

echo "Smoke test passed."
