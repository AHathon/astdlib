/*
 *    astdlib.cpp
 *  Arduino standard library for odd yet useful functions
 */
 
#include "astdlib.h"

void aprintf(const char *fmt, ...){
  char buf[128]; // resulting string limited to 128 chars
  va_list args;
  va_start (args, fmt);
  vsnprintf(buf, 128, fmt, args);
  va_end (args);
  Serial.print(buf);
}

char *hexDump(char *str, size_t strSize){
  static char buf[128];
  char *hex = "0123456789ABCDEF";
  u8 i = 0, j = 0;
  while(strSize--){
    u8 num1 = str[i] & 0xF;
    u8 num2 = (str[i] >> 4) & 0xF;
    
    buf[j] = hex[num2];
    buf[j+1] = hex[num1];
    i++;
    j+=2;
    buf[j] = ' ';
    j++;
  }
  return buf;
}

void hexPrint(char *str, size_t strSize){
    if(strSize > 0xFFFF) return;
    
	char buf[0x68] = {0};
	size_t s = strSize;
	int i=0, d=0, off=0;
	char c;
	while(s){
		off = (strSize-s);
		d = MIN(s, 16);
        sprintf(buf, "%0.4X| %s| ", str+off, hexDump((char*)(str+off), d));
		for(i = 0; i < d; i++){
			if(*(str+off+i) < 0x20 || *(str+off+i) > 0xFF) c = '.';
			else c = *(str+off+i);
			*(buf+0x38+i) = c;
		}
		Serial.println(buf);
		s-=d;
	}
	Serial.println("------------------------------------------------------------");
}

#define CRC32C_POLY 0x82F63B78
u32 crc32c(const void *buf, size_t len) {
	const u8 *cbuf = (const u8 *)buf;
	u32 crc = 0xFFFFFFFF;
	while (len--) {
		crc ^= *cbuf++;
		for (u32 i = 0; i < 8; i++)
			crc = crc & 1 ? (crc >> 1) ^ CRC32C_POLY : crc >> 1;
	}
	return ~crc;
}

#define FNV64_PRIME 0x00000100000001b3
#define FNV64_BASIS 0xCBF29CE484222325
u64 FNV1A64(const char *str){
    int len = strlen(str);
    const u64 fnv64Offset = FNV64_BASIS;
    const u64 fnv64Prime = FNV64_PRIME;
    u64 hash = fnv64Offset;

    for (int i = 0; i < len; i++)
    {
        hash = hash ^ str[i];
        hash *= fnv64Prime;
    }

    return hash;
}
