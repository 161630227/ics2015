#include "common.h"
#ifndef __CACHE_H__
#define __CACHE_H__

typedef struct
{
	bool dirty;
	bool valid;
	uint8_t block[64];
	uint32_t tag;

}cacheline;
typedef struct
{
	cacheline cache_line[N];

}cache_NAME;
#endif
cache_NAME cache_LEVEL[SET_SIZE];

