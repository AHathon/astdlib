/*
 *    astdlib.h
 *  Arduino standard library for odd yet useful functions
 */
 
#pragma once
 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <Arduino.h>
#include "types.h"

#define MIN(x,y) ((x < y) ? x : y)

void aprintf(const char *str, ...);
char *hexDump(char *str, size_t strSize);
void hexPrint(char *str, size_t strSize);
u32 crc32c(const void *buf, size_t len);
u64 FNV1A64(const char *str);
