//#include "cache-template.h"

#define NAME 1
#define N 8
#define SET_SIZE 128
#define LEVEL l1
#define BLOCK_SIZE 64
#define GET_SET_INDEX 0x00001fc0
#define BLOCK_BYTE 6
#define GET_BLOCK_OFFSET 0x3f
#define cache_LEVEL concat(cache_,LEVEL)
#define cache_N concat(cache_,NAME)
#define GET_HEAD_ADDR 0xffffffc0
#include "cache-template.h"

#undef N
#undef SET_SIZE
#undef LEVEL
#undef BLOCK_SIZE
#undef GET_SET_INDEX
#undef BLOCK_BYTE
#undef GET_BLOCK_OFFSET
#undef GET_HEAD_ADDR
#undef NAME
#undef cache_LEVEL


#define NAME 2
#define N 16
#define SET_SIZE 4096
#define LEVEL l2
#define BLOCK_SIZE 64
#define GET_SET_INDEX 0x0003ffc0
#define BLOCK_BYTE 6
#define GET_BLOCK_OFFSET 0x3f
#define cache_LEVEL concat(cache_,LEVEL)
#define cache_N concat(cache_,NAME)
#define GET_HEAD_ADDR 0xffffffc0
#include "cache-template.h"
#undef N
#undef SET_SIZE
#undef LEVEL
#undef BLOCK_SIZE
#undef GET_SET_INDEX
#undef BLOCK_BYTE
#undef GET_BLOCK_OFFSET
#undef GET_HEAD_ADDR
#undef NAME
void cache_init()
{
	int i,j;
//       for (i=0;i<4096;i++)
//       {
//	       for (j=0;j<16;j++)
		for (i=0;i<128;i++)
	{
		for(j=0;j<8;++j)
	       {
		cache_l1[i].cache_line[j].valid=false;
		       cache_l1[i].cache_line[j].valid=false;
	       cache_l2[i].cache_line[j].dirty=false;

	       }
       }

	for (i=0;i<128;i++)
	{
		for(j=0;j<8;++j)
		{
			cache_l1[i].cache_line[j].valid=false;
		}
	}
}
