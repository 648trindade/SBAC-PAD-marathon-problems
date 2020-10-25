#!/bin/bash

# Get the current directory so you can invoke it from anywhere
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

INPUTS=$DIR/../../misc/inputs

$DIR/dna $INPUTS/B.in $INPUTS/B-query.in problem_output