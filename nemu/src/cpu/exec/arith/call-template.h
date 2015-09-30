#include "cpu/exec/template-start.h"
#include "cpu/exec/helper.h"
#include "cpu/reg.h"

#define instr call

/*#if DATA_BYTE == 2 || DATA_BYTE == 4
static void do_execute() {
		cpu.esp=cpu.esp-4;
		swaddr_write(cpu.esp+1,4,cpu.eip);
		cpu.eip+=op_src->val;

					
		print_asm_template1();
}

make_instr_helper(i)
#endif*/

/*void push_eip(int size)
{
	    REG(4)-=4;
	    MEM_W(REG(4),cpu.eip+size);
}*/
make_helper(concat(call_rel32_, SUFFIX))
{
	 
	//   push_eip(DATA_BYTE);
	   swaddr_t addr=instr_fetch(eip+1,DATA_BYTE);
	   cpu.eip+=addr;
	   print_asm_template1();
           return 1+DATA_BYTE;
}
make_helper(concat(call_rm32_, SUFFIX))
{
	    
            swaddr_t addr=instr_fetch(cpu.eip+1,DATA_BYTE);
	    //   push_eip(DATA_BYTE);
	       cpu.eip+=addr;
	       print_asm_template2();
	       return 1+DATA_BYTE;							         
}

#include "cpu/exec/template-end.h"

