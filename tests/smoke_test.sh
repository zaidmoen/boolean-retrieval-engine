#!/usr/bin/env bash

set -e

g++ -std=c++17 -Wall -Wextra -Wpedantic src/*.cpp -Iinclude -o boolean_retrieval_engine

precedence_output=$(printf 'index OR data AND missing\nexit\n' | ./boolean_retrieval_engine)
grep -q 'D1 (doc1.txt)' <<< "$precedence_output"
if grep -q 'D3 (doc3.txt)' <<< "$precedence_output"; then
    echo "AND must be evaluated before OR."
    exit 1
fi

group_output=$(printf '(index OR data) AND documents\nexit\n' | ./boolean_retrieval_engine)
grep -q 'D1 (doc1.txt)' <<< "$group_output"
grep -q 'D3 (doc3.txt)' <<< "$group_output"

echo "Smoke test passed."
