#include "cache.h"
#include <stdlib.h>
uint32_t dram_read(hwaddr_t addr, size_t len);
uint32_t dram_read(hwaddr_t addr, size_t len);
uint32_t dram(hwaddr_t addr,size_t len);
void dram_write(hwaddr_t addr,size_t len,uint32_t data);

void hwaddr_write(hwaddr_t addr, size_t len, uint32_t data);
uint32_t concat(cache_read_,LEVEL)(bool *hit,uint32_t addr, size_t len)
{
	uint32_t set_index=(addr& GET_SET_INDEX)>>BLOCK_BYTE;
	uint32_t i;
	uint32_t block_offset=addr &GET_BLOCK_OFFSET;
        uint32_t addr_me=addr&GET_HEAD_ADDR;
    	//    printf("N=0x%x\n",N);
	for(i=0;i<N;++i)
	{
		uint32_t max=cache_LEVEL[set_index].cache_line[i].tag+BLOCK_SIZE;
		if((cache_LEVEL[set_index].cache_line[i].tag==addr_me)&&cache_LEVEL[set_index].cache_line[i].valid==true)
		{
	        
			if(addr+len>max)
			{
				uint32_t count=64-block_offset;
			//	bool hit2=false;
				uint32_t result=dram_read(addr+count,len-count)&(~0u >> ((4 - len) << 3));
//				uint32_t result=concat(cache_read_,LEVEL)(&hit2,addr+count,len-count);
				printf("result1=%x",result);
//				printf("result2=%x\n",dram_read(addr+count,len-count)&(~0u >> ((4 - len) << 3)));
				int j;
//				if(hit2)
//				{
					*hit=true;
					uint32_t index;
					index=cache_LEVEL[set_index].cache_line[i].block[63];
					printf("36行index=%x\n",index);
					for(j=62;j>=block_offset;j--)
				       {
					       index<<=8;
					       index+=cache_LEVEL[set_index].cache_line[i].block[j];
				       }
				        printf("dram=   cache=    %x   %x\n",dram(addr,len),(index+(result<<(8*count))));	
					return (index+(result<<(8*count)));
//				}
/*				else

				{
				     
					*hit=false;
					//这里的return值有问题，理论上应该return -1
			//		return(dram_read(addr+count,len-count)&(~0u >> ((4 - len) << 3)));
					return -1;
				}
	*/		}
			else
			{
                         
				*hit=true;
				int j;
				uint32_t index2=cache_LEVEL[set_index].cache_line[i].block[block_offset+len-1];
		//	        printf("%%\n");	
				for (j=len-2;j>=0;--j)
                                {
					index2<<=8;
	//				printf("**");
					index2+=cache_LEVEL[set_index].cache_line[i].block[block_offset+j];
				}
		//	      printf("%x   dram=%x\n",len,dram_read(addr,len)& (~0u >> ((4 - len) << 3)));
			     // printf("index2= %x\n",index2);
			      return index2;
				//	return *(uint32_t *)(&(cache_LEVEL[set_index].cache_line[i].block[block_offset]));
			}
			
		}
		
	}
	*hit=false;
	//printf("*\n");
	return -1;
}

bool concat(cache_write_,LEVEL)(uint8_t *data,uint32_t addr,uint32_t size,bool not_read,bool l2)
{
	uint32_t set_index=(addr & GET_SET_INDEX)>>BLOCK_BYTE;
	int i;
	uint32_t head_addr=addr & GET_HEAD_ADDR;

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
	//	printf("data=%x\n",data);
		if(cache_LEVEL[set_index].cache_line[i].valid==false)
		{
            
			cache_LEVEL[set_index].cache_line[i].tag=head_addr;
			int j;
			for (j=0;j<BLOCK_SIZE;j++)
				cache_LEVEL[set_index].cache_line[i].block[j]=dram_read(head_addr+j,1);
			cache_LEVEL[set_index].cache_line[i].valid=true;
			uint32_t count=64-block_offset;
			if (addr+size>(head_addr+64))
			{
				//hwaddr_write(addr+count,size-count,(uint32_t)data+count);
				bool hit=cache_write_l1(data+count,addr+count,size-count,1,0);
				if(hit) dram_write(addr+count,size-count,(uint32_t)data+count);
				else
				{
//					cache_write_l1(data+count,addr+count,size-count,0,0);
					dram_write(addr+count,size-count,(uint32_t)data+count);
				}
				for (j=0;j<count;j++)
				{
                                    cache_LEVEL[set_index].cache_line[i].block[block_offset+j]=*(data+j);
				}
			}
			else
			for (j=0;j<size;j++,data++)
			{
			//	printf("j=%x\n",*data);
				cache_LEVEL[set_index].cache_line[i].block[block_offset+j]=*data;
                       // printf("data%x\n",*data);
			}
			//printf("cache%x\n",cache_LEVEL[set_index].cache_line[i].block[block_offset]);
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
