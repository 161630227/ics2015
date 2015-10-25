#include "common.h"
#include"../../lib-common/x86-inc/mmu.h"
#include "cpu/reg.h"
//void L2_cache_write_L(hwaddr_t,size_t,uint32_t);
// Memory accessing interfaces */
uint32_t cache_read_l1(bool *hit,uint32_t addr,uint32_t len);
bool cache_write_l1(uint32_t *data,uint32_t byte,uint32_t addr,uint32_t size,bool not_read,bool l2);
 uint32_t page_translate(lnaddr_t addr);
uint32_t cache_read_l2(bool *hit,uint32_t addr,uint32_t len);
bool cache_write_l2(uint32_t *data,uint32_t byte,uint32_t addr,uint32_t size,bool not_read,bool l2);
uint32_t dram_read(hwaddr_t addr, size_t len);
void dram_write(hwaddr_t addr, size_t len, uint32_t data);
uint32_t hwaddr_read(hwaddr_t addr, size_t len) {
    
//	printf("内存%x\n",addr);
	assert(len==1||len==2||len==4);
//       if(addr==0x7fffffc)printf("jeremy= %x\n",addr);	
	bool data_hit=false;
	uint32_t result;
        result=cache_read_l1(&data_hit,addr,len);
	if(data_hit)
	return result & (~0u >> ((4 - len) << 3));
	else
	{
	
//		result=cache_read_l2(&data_hit,addr,len);
//		if(data_hit)
	//		return result& (~0u >> ((4 - len) << 3));
 //	else
   //            {

			result=dram_read(addr,len);
                         
         //  	cache_write_l1(&result,0,addr,len,0,0);
     //         }
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

 //      cache_write_l1(&data,0,addr,len,0,0);
     // if(addr==0x7f5ffa0)printf("fuck22\n");    
       dram_write(addr,len,data);
 //      printf("***\n");
//			cache_write_l2(&data,addr,len,0,1);
//                }
	}
      
//	cache_write(addr,len,data);
//	dram_write(addr, len, data);
}

uint32_t lnaddr_read(lnaddr_t addr, size_t len) {
        if(cpu.cr0.paging==1&&cpu.cr0.protect_enable==1)
	{
		uint32_t addr_index=page_translate(addr);
		return hwaddr_read(addr_index,len);
	}
	else
	return hwaddr_read(addr, len);
}
uint32_t page_translate(lnaddr_t addr)
{
        addr&=0xffffff;
	uint32_t page_dir=addr>>22;
	uint32_t page_directory_addr=(cpu.cr3.page_directory_base)+(page_dir<<2);
       printf("%x\n",addr); 
     	uint32_t page_directory=hwaddr_read(page_directory_addr,4);
        assert((page_directory & 0x1)!=0);
	uint32_t page_addr=((addr>>12)&0x3ff)*4+(page_directory&0xfffff000);
	uint32_t page=hwaddr_read(page_addr,4);
	assert((page & 0x1)!=0);
	uint32_t physical_addr=(page&0xfffff000)+(addr&0xfff);
       return physical_addr;
}
void lnaddr_write(lnaddr_t addr, size_t len, uint32_t data) {
	if(cpu.cr0.paging==1&&cpu.cr0.protect_enable==1) 
	{
                uint32_t addr_index=page_translate(addr);
                hwaddr_write(addr_index,len,data);
	}
	else hwaddr_write(addr, len, data);
} 
lnaddr_t  seg_translate(uint32_t addr,size_t len,uint8_t sreg)

{
	// uint8_t rpl;权限管理还有offset问题暂时未考虑
	uint16_t selector;
	uint16_t reg_index;//段索引
	switch(sreg)
	{
		case 0 :{
				selector=cpu.es.selector;break;
			}
		case 1: {
				 selector=cpu.cs.selector;break;
			}
                case 2: {
				 selector=cpu.ss.selector;break;
		        }
		case 3: {
			          selector=cpu.ds.selector;break;
			}
		default :assert(0);
	}
	reg_index=(selector>>3)*8;
//	uint8_t ti=selector &0x4;
	uint8_t tmp[8]; 
	int i;
	for(i = 0; i < 8; ++ i) 
	tmp[i] = lnaddr_read(cpu.gdtr.base_addr + reg_index  + i, 1);
	SegDesc *segdesc = (SegDesc*)tmp;
	return (segdesc->base_31_24 << 24) + (segdesc->base_23_16 << 16) + 	segdesc->base_15_0 + addr;
}
uint32_t swaddr_read(swaddr_t addr, size_t len,uint8_t sreg) {
//#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
//#endif
//	printf("addr=%x\n",addr);
	
	if(cpu.cr0.protect_enable)
	{
		lnaddr_t lnaddr= seg_translate(addr, len, sreg);      
		return lnaddr_read(lnaddr, len)& (~0u >> ((4 - len) << 3));

	}
	else
		return lnaddr_read(addr,len)& (~0u >> ((4 - len) << 3));
//	      	return dram_read(addr,len) & (~0u >> ((4 - len) << 3));
}


void swaddr_write(swaddr_t addr, size_t len, uint32_t data,uint8_t sreg) {
//#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);

//#endif
	printf("%x\n",cpu.cr0.protect_enable);
     if(cpu.cr0.protect_enable)
       {
	       lnaddr_t lnaddr = seg_translate(addr, len, sreg);
        	lnaddr_write(lnaddr, len, data);
     }
       else
       	dram_write(addr,len,data);
}

