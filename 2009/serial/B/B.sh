#!/bin/bash

# Get the current directory so you can invoke it from anywhere
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

INPUTS=$DIR/../../misc/inputs

if [ ! -e $INPUTS/B.in ] || [ ! -e $INPUTS/B-query.in ]
then
  pushd $INPUTS >/dev/null
  rm -rf B.in B-query.in
  unzip -qq B.zip
  popd >/dev/null
fi

$DIR/dna $INPUTS/B.in $INPUTS/B-query.in problem_output