#!/bin/bash

# Get the current directory so you can invoke it from anywhere
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

$DIR/clique < $DIR/../../misc/inputs/G.in