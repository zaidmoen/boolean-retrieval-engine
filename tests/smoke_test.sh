#!/usr/bin/env bash

set -e

g++ -std=c++17 -Wall -Wextra -Wpedantic src/*.cpp -Iinclude -o boolean_retrieval_engine

precedence_output=$(printf 'retrieval OR data AND missing\nexit\n' | ./boolean_retrieval_engine)
precedence_matches=$(grep 'Matching documents:' <<< "$precedence_output")
grep -q 'D1 (doc1.txt)' <<< "$precedence_matches"
if grep -q 'D3 (doc3.txt)' <<< "$precedence_matches"; then
    echo "AND must be evaluated before OR."
    exit 1
fi

group_output=$(printf '(index OR data) AND documents\nexit\n' | ./boolean_retrieval_engine)
group_matches=$(grep 'Matching documents:' <<< "$group_output")
grep -q 'D1 (doc1.txt)' <<< "$group_matches"
grep -q 'D3 (doc3.txt)' <<< "$group_matches"

not_output=$(printf 'NOT (information OR data)\nexit\n' | ./boolean_retrieval_engine)
not_matches=$(grep 'Matching documents:' <<< "$not_output")
grep -q 'D2 (doc2.txt)' <<< "$not_matches"

recovery_output=$(printf 'index AND\nretrieval\nexit\n' | ./boolean_retrieval_engine)
grep -q 'Invalid query:' <<< "$recovery_output"
recovery_matches=$(grep 'Matching documents:' <<< "$recovery_output")
grep -q 'D1 (doc1.txt)' <<< "$recovery_matches"
grep -q 'D2 (doc2.txt)' <<< "$recovery_matches"

case_output=$(printf 'InDeX aNd ReTrIeVaL\nexit\n' | ./boolean_retrieval_engine)
case_matches=$(grep 'Matching documents:' <<< "$case_output")
grep -q 'D1 (doc1.txt)' <<< "$case_matches"
grep -q 'D2 (doc2.txt)' <<< "$case_matches"

echo "Smoke test passed."
