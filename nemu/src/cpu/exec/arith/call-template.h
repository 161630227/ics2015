#include "cpu/exec/template-start.h"
#include "cpu/exec/helper.h"
#include "cpu/reg.h"

#define instr call
make_helper(concat(call_rel32_, SUFFIX))
{
	 
	   
	   swaddr_t addr=instr_fetch(eip+1,DATA_BYTE);
//printf("%x\n",addr);
	   cpu.esp-=DATA_BYTE;
	   MEM_W(cpu.esp,cpu.eip+DATA_BYTE);
	   cpu.eip+=addr;
	   if (DATA_BYTE==2)
		   cpu.eip&=0xffff;
//printf("%x\n",cpu.eip);
//printf("%x\n",op_src->val);
	   print_asm_template1();
           return 1+DATA_BYTE;
}
make_helper(concat(call_rm32_, SUFFIX))
{
	    
            swaddr_t addr=instr_fetch(cpu.eip+1,DATA_BYTE);
	       cpu.esp-=DATA_BYTE;
	       MEM_W(cpu.esp,cpu.eip+DATA_BYTE);
	       cpu.eip+=addr;
	       print_asm_template2();
	       return 1+DATA_BYTE;							         
}

#include "cpu/exec/template-end.h"

