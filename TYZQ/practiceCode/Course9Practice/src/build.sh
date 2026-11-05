#!/usr/bin/env bash

gcc -std=c11 -Wall -Wextra -g main.c student.c input.c -o ../builds/srms && ../builds/srms
