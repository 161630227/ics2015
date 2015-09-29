
#include "cpu/exec/template-start.h"
#include "cpu/exec/helper.h"
#include "cpu/reg.h"

#define instr pop

//#if DATA_BYTE == 2 || DATA_BYTE == 4
static void do_execute() {
	//	cpu.esp=cpu.esp+DATA_BYTE;

	      //	swaddr_write(op_dst,DATA_BYTE,op_src->val);
	     //	swaddr_write(dest, DATA_BYTE,REG[R_ESP], DATA_BYTE);
	       if (DATA_BYTE==4) OPERAND_W(op_dest, reg_l(R_ESP));
	       else OPERAND_W(op_dest,reg_w(R_ESP)); 
	       cpu.esp=cpu.esp+DATA_BYTE;
		print_asm_template1();
}
make_instr_helper(r)
make_instr_helper(rm)
//#if DATA_BYTE==2||DATA_BYTE==4
//make_instr_helper(si)
//#endif
#include "cpu/exec/template-end.h"

