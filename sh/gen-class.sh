#!/bin/bash


CLASS_NAME=$1
CLASS_DIR="./$CLASS_NAME"
HEADER_TEMPLATE=$(<sh/templates/header.txt)
TEST_TEMPLATE=$(<sh/templates/test.txt)

TEMPLATE_REGEX="s/(%[A-Z].*%)/${CLASS_NAME}/g"

cd src/

create a directory of name
if OUTPUT=$(mkdir $CLASS_DIR); then
  echo "Directory created at: $CLASS_DIR"
else
  echo "Failed to create directory at: $CLASS_DIR"
  echo "$OUTPUT"
  exit 1
fi

cd $CLASS_DIR

# create header file, 
echo "$HEADER_TEMPLATE" | perl -pe $TEMPLATE_REGEX > $CLASS_NAME.h
echo "$TEST_TEMPLATE" | perl -pe $TEMPLATE_REGEX > $CLASS_NAME.test.h

echo "[Done] Finished generating CLASS_NAME files"

echo "Header path: src/$CLASS_NAME/$CLASS_NAME.h"
echo "Test path: ../../src/$CLASS_NAME/$CLASS_NAME.test.h"