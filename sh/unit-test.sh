#!/bin/bash

cd ./test
make clean
make

if make run ; then
  make clean
  echo "*** Tests successfull ***"
  exit 0
else
  make clean
  echo "*** Tests failed ***"
  exit 1
fi
