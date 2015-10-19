#include "common.h"
#include "cpu/reg.h"
/*uint32_t dram_read(hwaddr_t,size_t);
void dram_write(hwaddr_t, size_t,uint32_t);
uint32_t cache_read(hwaddr_t,size_t);
void cache_write(hwaddr_t,size_t, uint32_t);
//void L2_cache_write_L(hwaddr_t,size_t,uint32_t);
 Memory accessing interfaces */
uint32_t cache_read_l1(bool *hit,uint32_t addr,uint32_t len);
bool cache_write_l1(uint32_t *data,uint32_t addr,uint32_t size,bool not_read,bool l2);
uint32_t cache_read_l2(bool *hit,uint32_t addr,uint32_t len);
bool cache_write_l2(uint32_t *data,uint32_t addr,uint32_t size,bool not_read,bool l2);
uint32_t dram_read(hwaddr_t addr, size_t len);
void dram_write(hwaddr_t addr, size_t len, uint32_t data);
uint32_t hwaddr_read(hwaddr_t addr, size_t len) {
    
	assert(len==1||len==2||len==4);
	bool data_hit=false;
	uint32_t result=cache_read_l1(&data_hit,addr,len);
	if(data_hit)
	 return result & (~0u >> ((4 - len) << 3));
	else
	{
	
	//	printf("^**\n");
//		result=cache_read_l2(&data_hit,addr,len);
               // printf("aaaaa\n");
	//	if(data_hit)
	//		return result& (~0u >> ((4 - len) << 3));
//  	else
  //              {

		
			result=dram_read(addr,len);
			printf("result= %x\n",result);

                   	cache_write_l1(&result,addr,len,0,0);
    //          }
	}


	return  result & (~0u >> ((4 - len) << 3));
	
//	return cache_read(addr,len)&(~0u >> ((4 - len) << 3));

//	return dram_read(addr, len) & (~0u >> ((4 - len) << 3));

}


void hwaddr_write(hwaddr_t addr, size_t len, uint32_t data) {
        assert(len==1||len==2||len==4);
	bool hit=cache_write_l1(&data,addr,len,1,0);
	if(hit)
		dram_write(addr,len,data);
	else
	{
	
//		hit= cache_write_l2(&data,addr,len,1,1);
//		if(!hit)
//		{

 //       cache_write_l1(&data,addr,len,0,0);
    	dram_write(addr,len,data);
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

