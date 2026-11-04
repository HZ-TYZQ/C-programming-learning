#!/bin/bash

gcc -std=c11 -Wall -Wextra -g test.c student.c -o test_srms &&
  ./test_srms
