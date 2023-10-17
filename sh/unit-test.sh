#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

cd ./test
make clean

if OUTPUT=$(make) ; then
  echo -e "${GREEN}Compile successfull${NC}"
else
  # echo "${RED}${OUTPUT}${NC}"
  echo -e "${RED}Compile failed${NC}"
  exit 1
fi

if OUTPUT=$(make run) ; then
  make clean
  # echo "$OUTPUT"
  echo -e "${GREEN}Tests successfull${NC}"
  exit 0
else
  make clean
  echo "$OUTPUT" | perl -pe "s/(failed)/${RED}failed${NC}/g"
  echo -e "${RED}Tests failed${NC}"
  exit 1
fi
