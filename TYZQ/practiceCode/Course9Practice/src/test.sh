#!/bin/bash

gcc -std=c11 -Wall -Wextra -g test.c student.c -o ../builds/test_srms &&
  ../builds/test_srms
