
#include "cpu/exec/template-start.h"

#define instr je
static void do_execute(){
//	DATA_TYPE_S result = op_dest->val - op_src->val;
	
	/* TODO: Update EFLAGS. */
	if(cpu.eflags.ZF==1)
	{
		cpu.eip=cpu.eip+op_src->val;
	}
print_asm_template1();
}

//#if (DATA_BYTE == 2 || DATA_BYTE == 4)
make_instr_helper(i)
//#endif
#include "cpu/exec/template-end.h"
