#include "cpu/exec/template-start.h"

#define instr movsx

/*static void do_execute() {
	OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}*/
make_helper(concat(movsx_rmb2r_, SUFFIX)) {
   //	swaddr_t addr = instr_fetch(eip + 1, 4);
    //	MEM_W(addr, REG(R_EAX));
	DATA_TYPE index=op_src->val;
	OPERAND_W(op_dest,index);
        print_asm_template2();
	return (3+DATA_BYTE);
}

make_helper(concat(movsx_rmw2r_, SUFFIX)) {
//	swaddr_t addr = instr_fetch(eip + 1, 4);
	DATA_TYPE index=op_src->val;
	OPERAND_W(op_dest,index);
        print_asm_template2();
	return 5;
}

#include "cpu/exec/template-end.h"
