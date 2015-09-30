#include "cpu/exec/template-start.h"
#include "cpu/reg.h"
#define instr cwd

make_helper(concat(cwd_, SUFFIX)) {
   //	swaddr_t addr = instr_fetch(eip + 1, 4);
    //	MEM_W(addr, REG(R_EAX));
	if(DATA_BYTE==2) 
	{
		if(reg_w(R_AX)<0)
			reg_w(R_DX)=0xffff;
		else reg_w(R_DX)=0;
	}
	else
	if(DATA_BYTE==4)
	{
		if(cpu.eax<0)
			cpu.edx=0xffffffff;
		else cpu.edx=0;
	}
	//OPERAND_W(op_dest,index);
        print_asm_template2();
	return 1;
}
#include "cpu/exec/template-end.h"
