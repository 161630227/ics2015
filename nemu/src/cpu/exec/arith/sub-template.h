/*
#include "cpu/exec/template-start.h"

#define instr sub
static void do_execute(){
	DATA_TYPE_S result = op_dest->val - op_src->val;
	OPERAND_W(op_dest, result);

	/* TODO: Update EFLAGS. */
	DATA_TYPE_S index=result;
        cpu.eflgas.CF=result<op_dest->val;
	cpu.eflgas.ZF=(result==0);
	cpu.eflgas.PF=1;
	while (index)
       {
	       if(index&0x1) cpu.eflgas.PF!=cpu.eflgas.PF;
	       index&=(index-1);
        }
        cpu.eflgas.AF=(result^(op_dest->val))>>4;
        cpu.eflgas.SF=result<0;
        cpu.eflgas.OF=(((op_src->val<0)!=(op_dest->val<0))&&((op_dest->val<0)!=(result<0)));
//	panic("please implement me");
print_asm_template2();
}
//make_instr_helper(i2r)
//make_instr_helper(i2rm)
//make_instr_helper(r2rm)
//make_instr_helper(rm2r)
//make_instr_helper(rm_imm)
//#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
//#endif
#include "cpu/exec/template-end.h"*/
