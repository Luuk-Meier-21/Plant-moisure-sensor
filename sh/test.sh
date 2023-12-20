#!/bin/bash

cd ./test
make clean

echo ""

echo "[Starting] Test compilation 'test.ino'"
if OUTPUT=$(make) ; then
  echo "[Done] Test compilation successfull"
else
  echo "[Error] Test compilation failed"
  # echo "$OUTPUT"
  exit 1
fi

echo "[Starting] Testing"
echo 
if OUTPUT=$(make run) ; then
  make clean
  echo "$OUTPUT"
  echo "[Done] Tests successfull"
  exit 0
else
  make clean
  echo "$OUTPUT"
  echo "[Error] Tests failed"
  exit 1
fi
