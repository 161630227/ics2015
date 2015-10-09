#include "cpu/exec/template-start.h"

#define instr inc

static void do_execute () {
	DATA_TYPE result = op_src->val + 1;
	OPERAND_W(op_src, result);
       
	DATA_TYPE_S index=result;
        //cpu.eflags.CF=result<op_dest->val;
	cpu.eflags.ZF=(result==0);
	cpu.eflags.PF=1;
        cpu.eflags.SF=index<0;
	while (index)
       {
	       if(index&0x1) cpu.eflags.PF=!cpu.eflags.PF;
	       index&=(index-1);
        }
        cpu.eflags.AF=(result^(op_src->val))>>4;
        if(MSB(op_src->val) == 0 && MSB(result) != MSB(op_src->val))
	   cpu.eflags.OF = 1; else cpu.eflags.OF = 0;

	print_asm_template1();
}

make_instr_helper(rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(r)
#endif

#include "cpu/exec/template-end.h"
