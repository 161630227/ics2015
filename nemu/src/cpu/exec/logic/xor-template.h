#include "cpu/exec/template-start.h"

#define instr xor

static void do_execute () {
	DATA_TYPE result = op_dest->val ^ op_src->val;
	OPERAND_W(op_dest, result);

        cpu.eflags.OF=0;
	cpu.eflags.CF=0;
	cpu.eflags.ZF=(result==0);
	cpu.eflags.PF=1;
	DATA_TYPE_S index=result;
        cpu.eflags.SF=index<0;
	while (index)
       {
	       if(index&0x1) cpu.eflags.PF=!cpu.eflags.PF;
	       index&=(index-1);
        }
	print_asm_template2();
}

make_instr_helper(i2a)
make_instr_helper(i2rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif
make_instr_helper(r2rm)
make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
