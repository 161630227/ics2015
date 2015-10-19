#include "cache.h"
#include <stdlib.h>
uint32_t dram_read(hwaddr_t addr, size_t len);
uint32_t dram(hwaddr_t addr,size_t len);
void dram_write(hwaddr_t addr,size_t len,uint32_t data);
uint32_t concat(cache_read_,LEVEL)(bool *hit,uint32_t addr,uint32_t len)
{
	uint32_t set_index=(addr& GET_SET_INDEX)>>BLOCK_BYTE;
	uint32_t i;
//	uint32_t n=10;
//	printf("%x\n",addr);
//	printf("%s\n",LEVEL);
	uint32_t block_offset=addr &GET_BLOCK_OFFSET;
        uint32_t addr_me=addr&GET_HEAD_ADDR;
    	//    printf("N=0x%x\n",N);
	for(i=0;i<N;++i)
	{
//		printf("%d\n",n);
//		printf("i%d %d\n",i, i < N);
		
		uint32_t max=cache_LEVEL[set_index].cache_line[i].tag+BLOCK_SIZE;
		if((cache_LEVEL[set_index].cache_line[i].tag==addr_me)&&cache_LEVEL[set_index].cache_line[i].valid==true)
		{
	        
		//	printf("%d\n",cache_LEVEL[set_index].cache_line[i].valid);
			if(addr+len>max)
			{
			//	uint8_t temp[4]={0,0,0,0};
				uint32_t count=64-block_offset;
				bool hit2=false;
				uint32_t result=concat(cache_read_,LEVEL)(&hit2,addr+count,len-count);
				int j;
				if(hit2)
				{
					*hit=true;
					uint32_t index;
					index=cache_LEVEL[set_index].cache_line[i].block[block_offset];
					for(j=1;j<count;j++,block_offset++)
				       {
					       index<<=8;
					       index+=cache_LEVEL[set_index].cache_line[i].block[block_offset];
				       }
					
					return (index<<8*(len-count))+result;
				}
				else

				{
				     
					*hit=false;
					return -1;
				}
			}
			else
			{
                         
				*hit=true;
				int j;
				uint32_t index2=cache_LEVEL[set_index].cache_line[i].block[block_offset];
				for (j=1;j<len;++j)
                                {
					index2<<=8;
					index2+=cache_LEVEL[set_index].cache_line[i].block[block_offset+j];
				}
			      return index2;
				//	return *(uint32_t *)(&(cache_LEVEL[set_index].cache_line[i].block[block_offset]));
			}
			
		}
		
	}
	*hit=false;
	printf("*\n");
	return -1;
}

bool concat(cache_write_,LEVEL)(uint8_t *data,uint32_t addr,uint32_t size,bool not_read,bool l2)
{
	uint32_t set_index=(addr & GET_SET_INDEX)>>BLOCK_BYTE;
	int i;
	uint32_t head_addr=addr & GET_HEAD_ADDR;
	printf("datahere %x\n",*data);
	uint32_t block_offset=addr & GET_BLOCK_OFFSET;
	if(not_read)
	{
		for(i=0;i<N;i++)
		{

		  
			if(cache_LEVEL[set_index].cache_line[i].tag<=addr &&cache_LEVEL[set_index].cache_line[i].tag+BLOCK_SIZE>addr &&cache_LEVEL[set_index].cache_line[i].valid==true)
			{
				int j;
				for (j=0;j<size;j++,data++,block_offset++)
					cache_LEVEL[set_index].cache_line[i].block[block_offset]=*data;
				if(l2)
					cache_LEVEL[set_index].cache_line[i].dirty=true;
				return true;
                        }
		}
		return false;

	}
	for (i=0;i<N;i++)
	{
		printf("%x\n",*data);
		if(cache_LEVEL[set_index].cache_line[i].valid==false)
		{
            
			cache_LEVEL[set_index].cache_line[i].tag=head_addr;
			int j;
	//		for (j=0;j<BLOCK_SIZE;j++,head_addr++)
	//			cache_LEVEL[set_index].cache_line[i].block[j]=dram_read(head_addr,1);
			printf("^ _ ^\n");
			cache_LEVEL[set_index].cache_line[i].valid=true;
			for (j=0;j<size;j++,data++)
			{
				printf("j=%x\n",*data);
				cache_LEVEL[set_index].cache_line[i].block[block_offset+j]=*data;
                       // printf("data%x\n",*data);
			}
			printf("cache%x\n",cache_LEVEL[set_index].cache_line[i].block[block_offset]);
			if(l2)
				cache_LEVEL[set_index].cache_line[i].dirty=true;
                  return true;                   
		}
	}
	int ran=rand()%N;
	//  改过l1  before l2
	if(l2 &&cache_LEVEL[set_index].cache_line[ran].dirty==true)
	{
		for (i=0;i<BLOCK_SIZE;i++,cache_LEVEL[set_index].cache_line[ran].tag++)
			dram_write(cache_LEVEL[set_index].cache_line[ran].tag,1,cache_LEVEL[set_index].cache_line[ran].block[i]);

	}
	
	if(!l2&&cache_LEVEL[set_index].cache_line[ran].valid==true)
	{
		for (i=0;i<BLOCK_SIZE;i++,cache_LEVEL[set_index].cache_line[ran].tag++)
			dram_write(cache_LEVEL[set_index].cache_line[ran].tag,1,cache_LEVEL[set_index].cache_line[ran].block[i]);

	}
	cache_LEVEL[set_index].cache_line[ran].tag=head_addr;
	for (i=0;i<BLOCK_SIZE;i++,head_addr++)
		cache_LEVEL[set_index].cache_line[ran].block[i]=dram_read(head_addr,1);
	if(l2)
		cache_LEVEL[set_index].cache_line[ran].dirty=true;
	int j;
	for (j=0;j<size;j++,data++,block_offset++)
		cache_LEVEL[set_index].cache_line[ran].block[block_offset]=*data;
	return true;

}
