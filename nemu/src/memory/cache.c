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
//	int i,j;
//       for (i=0;i<4096;i++)
//       {
//	       for (j=0;j<16;j++)
/*		for (i=0;i<128;i++)
	{
		for(j=0;j<16;++j)
	       {
		cache_l2[i].cache_line[j].valid=false;
		     //  cache_l1[i].cache_line[j].valid=false;
	       cache_l2[i].cache_line[j].dirty=false;

	       }
       }*/
memset(cache_l1,0, sizeof(cache_l1));
memset(cache_l2,0, sizeof(cache_l2));
int i;
for (i=0;i<64;++i)
	tlb[i].valid=false;
/*	for (i=0;i<128;i++)
	{
		for(j=0;j<8;++j)
		{
			cache_l1[i].cache_line[j].valid=false;
		}
	}*/
}
uint32_t tlb_read(bool *hit,lnaddr_t addr)
{
	uint32_t vpage_num=(addr&0xfffff000)>>12;
	int i;
	for (i=0;i<64;++i)
	{
		if(vpage_num==tlb[i].tag&&tlb[i].valid==true)
		{
			*hit=true;
			return tlb[i].pa_head;
		}
	}
	*hit=false;
	return -1;
}
void tlb_write(uint32_t pa_head,uint32_t vpage_num)
{
	int i;
	for (i=0;i<64;++i)
	{
		if(tlb[i].valid==false)
		{
			tlb[i].tag=vpage_num;
			tlb[i].pa_head=pa_head;
			tlb[i].valid=true;
			return;
		}
	}
	uint32_t ran=random()%64;
	tlb[ran].tag=vpage_num;
	tlb[ran].pa_head=pa_head;

}
