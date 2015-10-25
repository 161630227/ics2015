#include "cpu/exec/template-start.h"
#include "cpu/decode/modrm.h"
#include "../../../../../lib-common/x86-inc/mmu.h"
#define instr mov

static void do_execute() {
	OPERAND_W(op_dest, op_src->val);
     //   printf("hhhh\n");
	print_asm_template2();
}

make_instr_helper(i2r)
make_instr_helper(i2rm)
make_instr_helper(r2rm)
make_instr_helper(rm2r)
make_helper(concat(mov_a2moffs_, SUFFIX)) {
	swaddr_t addr = instr_fetch(eip + 1, 4);
	MEM_W(addr, REG(R_EAX),DS);

	print_asm("mov" str(SUFFIX) " %%%s,0x%x", REG_NAME(R_EAX), addr);
	return 5;
}
make_helper(concat(mov_rm2sreg_,SUFFIX)){
	uint8_t m;
	m=instr_fetch(eip+1,1);
	uint8_t m_index;
	m_index=(m&0x38)>>3;
	uint16_t selector=REG(m&0x7);
	uint16_t reg_index;
	reg_index=(selector>>3)*8;
	uint8_t tmp[8]; 
	int i;
	for(i = 0; i < 8; ++ i)  
	tmp[i] = lnaddr_read(cpu.gdtr.base_addr + reg_index  + i, 1);
	SegDesc *segdesc = (SegDesc*)tmp;
	uint32_t base_addr;	
	base_addr=(segdesc->base_31_24 << 24) + (segdesc->base_23_16 << 16) +segdesc->base_15_0 ;
	switch(m_index){	
		case 0:
			{
				cpu.es.selector=REG(m&0x7);
		         	cpu.es.base_addr=base_addr;
				break;
			}
		case 1:
			{
				cpu.ds.selector=REG(m&0x7);
			        cpu.ds.base_addr=base_addr;
				break;
			}
		case 2:
			{
				cpu.ss.selector=REG(m&0x7);
			        cpu.ss.base_addr=base_addr;
				break;
			}
		case 3:
			{
				cpu.cs.selector=REG(m&0x7);
			        cpu.cs.base_addr=base_addr;
				break;
			}
		default :assert(0);
	}
			
print_asm("mov" str(SUFFIX) " %%%s,0x%x", REG_NAME(m&0x3), m&0x3);
//	print_asm("mov" str(SUFFIX) " %%%s,%%d", REG_NAME(m & 0x7), ((m >> 3) & 0x7));
	
        return 2;
}
make_helper(concat(mov_moffs2a_, SUFFIX)) {
	swaddr_t addr = instr_fetch(eip + 1, 4);
	REG(R_EAX) = MEM_R(addr,DS);
	print_asm("mov" str(SUFFIX) " 0x%x,%%%s", addr, REG_NAME(R_EAX));
	return 5;
}
make_helper(concat(mov_rm2cr_,SUFFIX)){
	uint32_t r=instr_fetch(eip+1,1);
	uint8_t index=(r&0x3f)>>3;
	if(index==0)cpu.cr0.val=REG(r&0x7);
	else cpu.cr3.val=REG(r&0x7);
	print_asm("mov" str(SUFFIX) " %%%s,%%%s", REG_NAME(r & 0x7), "cr0");
        return 2;
}

make_helper(concat(mov_cr2rm_,SUFFIX)){
	uint32_t r=instr_fetch(eip+1,1);
        uint8_t index=(r&0x3f)>>3;

	if(index==0)REG(r&0x7)= cpu.cr0.val;
	else REG(r&0x7)=cpu.cr3.val;
	print_asm("mov" str(SUFFIX) " %%%s,%%%s","cr0", REG_NAME(r & 0x7));
        return 2;
}
#include "cpu/exec/template-end.h"
