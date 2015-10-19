#include "cache.h"
#include <stdlib.h>
uint32_t dram_read(hwaddr_t addr, size_t len);
uint32_t dram_read(hwaddr_t addr, size_t len);
uint32_t dram(hwaddr_t addr,size_t len);
void dram_write(hwaddr_t addr,size_t len,uint32_t data);
bool cache_write_l1(uint32_t *data,uint32_t byte,uint32_t addr,uint32_t size,bool not_read,bool l2);
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
				bool hit2=false;
//				uint32_t result=dram_read(addr+count,len-count)&(~0u >> ((4 - len) << 3));
				uint32_t result=concat(cache_read_,LEVEL)(&hit2,addr+count,len-count);
//				printf("result1=%x\n",result);
				int j;
				uint32_t index;
				index=cache_LEVEL[set_index].cache_line[i].block[63];
				for(j=62;j>=block_offset;j--)
					 {
					       index<<=8;
					       index+=cache_LEVEL[set_index].cache_line[i].block[j];
				       }
				if(hit2)
				{
					*hit=true;
		//		        printf("dram=   cache=    %x   %x\n",dram(addr,len),(index+(result<<(8*count))));	
					return(index+(result<<(8*count)));
				}
				else

				{
				     
					*hit=false;
					uint32_t result2=dram_read(addr+count,len-count)&(~0u >> ((4 - len+count) << 3));
				        cache_write_l1(&result2,0,addr+count,len-count,0,0);
				         
					return(index+(result2<<(8*count)));
				}
			}
			else
			{
                         
				*hit=true;
				int j;
				uint32_t index2=cache_LEVEL[set_index].cache_line[i].block[block_offset+len-1];
				for (j=len-2;j>=0;--j)
                                {
					index2<<=8;
					index2+=cache_LEVEL[set_index].cache_line[i].block[block_offset+j];
				}
		//	      printf("%x   dram=%x\n",len,dram_read(addr,len)& (~0u >> ((4 - len) << 3)));
			     // printf("index2= %x\n",index2);
			      return index2;
			}
			
		}
		
	}
	*hit=false;
	return -1;
}

bool concat(cache_write_,LEVEL)(uint32_t* data,uint32_t byte,uint32_t addr,uint32_t size,bool not_read,bool l2)//data represent addr
{
	uint32_t set_index=(addr & GET_SET_INDEX)>>BLOCK_BYTE;
	int i;
//	printf("85读入数据%x\n",*data);
	uint32_t head_addr=addr & GET_HEAD_ADDR;

	uint32_t block_offset=addr & GET_BLOCK_OFFSET;
	if(not_read)
	{
		for(i=0;i<N;i++)
		{

		  
			if(cache_LEVEL[set_index].cache_line[i].tag==addr &&cache_LEVEL[set_index].cache_line[i].tag+BLOCK_SIZE>addr+size &&cache_LEVEL[set_index].cache_line[i].valid==true)
			{
				uint32_t data_index=((*data)>>(8*byte));
	                   	int data1=data_index&(~0u >> ((4 - size) << 3));
				memcpy(cache_LEVEL[set_index].cache_line[i].block+block_offset,&data1,size);
				if(l2)
					cache_LEVEL[set_index].cache_line[i].dirty=true;
				return true;
                        }
			else if(cache_LEVEL[set_index].cache_line[i].tag==head_addr&&cache_LEVEL[set_index].cache_line[i].valid==true)
			{
                                int count=64-size;
				bool hit=cache_write_l1(data+count,count,addr+count,size-count,1,0);
		//		if(hit) dram_write(addr+count,size-count,(uint32_t)data+count);
				if(!hit)
				{
					cache_write_l1(data+count,count,addr+count,size-count,0,0);
				//	dram_write(addr+count,size-count,(uint32_t)data+count);
				}
			
				uint32_t data_index=(*data)>>(8*byte);
	                   	int data1=data_index&(~0u >> ((4 - size) << 3));
				memcpy(cache_LEVEL[set_index].cache_line[i].block+block_offset,&data1,count);
		        }
		}
		return false;

	}
	for (i=0;i<N;i++)
	{
		if(cache_LEVEL[set_index].cache_line[i].valid==false)
		{
            
			cache_LEVEL[set_index].cache_line[i].tag=head_addr;
			int j;
			for (j=0;j<BLOCK_SIZE;j++)
			{	cache_LEVEL[set_index].cache_line[i].block[j]=dram_read(head_addr+j,1)&(~0u >> ((4 - 1) << 3));
			}
			cache_LEVEL[set_index].cache_line[i].valid=true;
			uint32_t count=64-block_offset;
			if (addr+size>(head_addr+64))
			{
				bool hit=cache_write_l1(data,count,addr+count,size-count,1,0);
				if(!hit)
				{
					cache_write_l1(data+count,0,addr+count,size-count,0,0);
				//	dram_write(addr+count,size-count,(uint32_t)data+count);
				}
			uint32_t data_index=(*data)>>(8*byte);
	                int data1=data_index&(~0u >> ((4 - size) << 3));
				memcpy(cache_LEVEL[set_index].cache_line[i].block+block_offset,&data1,count);
			}
			else
			{
				uint32_t data_index=(*data)>>(8*byte);
	                   	int data1=data_index&(~0u >> ((4 - size) << 3));
				memcpy(cache_LEVEL[set_index].cache_line[i].block+block_offset,&data1,size);
			}
			if(addr==0x10003e)
			{
				printf("data=%x\n",*data);
				printf("145行%x\n",cache_LEVEL[set_index].cache_line[i].block[block_offset]);
			        printf("146行%x\n",cache_LEVEL[set_index].cache_line[i].block[block_offset+1]);
			        bool data_hit=false;
				int rr=(addr+64-block_offset)&GET_SET_INDEX;
			       // int rr=(addr+64-block_offset)&GET_BLOCK_OFFSET;
				printf("index=%x\n",rr);	
			       	printf("cache  %x\n",cache_read_l1(&data_hit,0x10003e,4));
			        printf("147行%x\n",cache_LEVEL[40].cache_line[i].block[0]);
		                printf("148行%x\n",cache_LEVEL[40].cache_line[i].block[1]);
			}
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
		for (i=0;i<BLOCK_SIZE;i++)
			dram_write(cache_LEVEL[set_index].cache_line[ran].tag+i,1,cache_LEVEL[set_index].cache_line[ran].block[i]);

	}
	cache_LEVEL[set_index].cache_line[ran].tag=head_addr;
	for (i=0;i<BLOCK_SIZE;i++)
		cache_LEVEL[set_index].cache_line[ran].block[i]=dram_read(head_addr+i,1) & (~0u >> ((4 -3) << 3));
	if(l2)
		cache_LEVEL[set_index].cache_line[ran].dirty=true;
	uint32_t count1=64-block_offset;
	if (addr+size>(head_addr+64))
	{
	   bool hit=cache_write_l1(data+count1,count1,addr+count1,size-count1,1,0);
	  // if(hit) dram_write(addr+count1,size-count1,(uint32_t)data+count1);
	   if(!hit)
	  {
		cache_write_l1(data+count1,count1,addr+count1,size-count1,0,0);
	//	dram_write(addr+count1,size-count1,(uint32_t)data+count1);
	  }
	   
	    uint32_t data_index=((*data))>>(8*byte);
	    int data1=data_index&(~0u >> ((4 - size) << 3));
            memcpy(cache_LEVEL[set_index].cache_line[i].block+block_offset,&data1,count1);
          return true;
	}

	uint32_t data_index=(*data)>>(8*byte);
	int data1=data_index&(~0u >> ((4 - size) << 3));
	memcpy(cache_LEVEL[set_index].cache_line[i].block+block_offset,&data1,size);
	return true;

}
