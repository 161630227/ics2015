#include "common.h"
#include "cpu/reg.h"
/*uint32_t dram_read(hwaddr_t,size_t);
void dram_write(hwaddr_t, size_t,uint32_t);
uint32_t cache_read(hwaddr_t,size_t);
void cache_write(hwaddr_t,size_t, uint32_t);
//void L2_cache_write_L(hwaddr_t,size_t,uint32_t);
 Memory accessing interfaces */
uint32_t cache_read_l1(bool *hit,uint32_t addr,uint32_t len);
bool cache_write_l1(uint32_t *data,uint32_t byte,uint32_t addr,uint32_t size,bool not_read,bool l2);
uint32_t cache_read_l2(bool *hit,uint32_t addr,uint32_t len);
bool cache_write_l2(uint32_t *data,uint32_t byte,uint32_t addr,uint32_t size,bool not_read,bool l2);
uint32_t dram_read(hwaddr_t addr, size_t len);
void dram_write(hwaddr_t addr, size_t len, uint32_t data);
uint32_t hwaddr_read(hwaddr_t addr, size_t len) {
    
	assert(len==1||len==2||len==4);
//       if(addr==0x7fffffc)printf("jeremy= %x\n",addr);	
	bool data_hit=false;
	uint32_t result;
	//int data1=0x1ac;
//	 memcpy(cache_LEVEL[set_index].cache_line[i].block+block_offset,&data1,size);
//	printf("read_addr=%x\n",addr);
//	printf("11=%x\n",cache_read_l1(&data_hit,0x7f5fffd,4));
        result=cache_read_l1(&data_hit,addr,len);
	if(data_hit)
	return result & (~0u >> ((4 - len) << 3));
	else
	{
	
//		result=cache_read_l2(&data_hit,addr,len);
	//	if(data_hit)
	//		return result& (~0u >> ((4 - len) << 3));
//  	else
  //              {

			result=dram_read(addr,len);
                         
//              	cache_write_l1(&result,0,addr,len,0,0);
    //          }
	}

       
// printf("addr=%x\n",addr);
	return  result & (~0u >> ((4 - len) << 3));
	
//	return cache_read(addr,len)&(~0u >> ((4 - len) << 3));

//	return dram_read(addr, len) & (~0u >> ((4 - len) << 3));

}


void hwaddr_write(hwaddr_t addr, size_t len, uint32_t data) {
        assert(len==1||len==2||len==4);
	bool hit=cache_write_l1(&data,0,addr,len,1,0);
        if(len==0) printf("80行 addr=%x\n",addr);

	//	bool hit=true;
//     printf("addr= %x len= %x  hit= %x data%x\n",addr,len,hit,data);	
	if(hit)
		dram_write(addr,len,data);
	else
	{
	
//		hit= cache_write_l2(&data,addr,len,1,1);
//		if(!hit)
//		{

       cache_write_l1(&data,0,addr,len,0,0);
      if(addr==0x7f5ffa0)printf("fuck22\n");    
       dram_write(addr,len,data);
 //      printf("***\n");
//			cache_write_l2(&data,addr,len,0,1);
//                }
	}
      
//	cache_write(addr,len,data);
//	dram_write(addr, len, data);
}

uint32_t lnaddr_read(lnaddr_t addr, size_t len) {
	return hwaddr_read(addr, len);
}

void lnaddr_write(lnaddr_t addr, size_t len, uint32_t data) {
	hwaddr_write(addr, len, data);
}

uint32_t swaddr_read(swaddr_t addr, size_t len) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	return lnaddr_read(addr, len);
}

void swaddr_write(swaddr_t addr, size_t len, uint32_t data) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	lnaddr_write(addr, len, data);
}

