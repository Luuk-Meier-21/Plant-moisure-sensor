#!/bin/bash

RED='\033[1;31m'
GREEN='\033[1;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

# 1. Test
cd ./test
make clean

echo -e "${YELLOW}Compiling test...${NC}"
if OUTPUT=$(make) ; then
  echo -e "${GREEN}Test compiliation successfull${NC}"
else
  # echo "${RED}${OUTPUT}${NC}"
  echo -e "${RED}Test compiliation failed${NC}"
  exit 1
fi

echo -e "${YELLOW}Testing...${NC}"
if OUTPUT=$(make run) ; then
  make clean
  # echo "$OUTPUT"
  echo -e "${GREEN}Tests successfull${NC}"
else
  make clean
  echo "$OUTPUT" | perl -pe "s/(failed)/${RED}failed${NC}/g"
  echo -e "${RED}Tests failed${NC}"
  exit 1
fi

cd ../

# 2. Compile
echo -e "${YELLOW}Compiling sketch...${NC}"
if OUTPUT=$(arduino-cli compile) ; then
  echo -e "${GREEN}Compile successfull${NC}"
else
  # echo "${RED}${OUTPUT}${NC}"
  echo -e "${RED}Compile failed${NC}"
  exit 1
fi

# 2. Upload


