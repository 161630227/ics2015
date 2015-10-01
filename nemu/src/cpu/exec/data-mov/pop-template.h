
#include "cpu/exec/template-start.h"
#include "cpu/exec/helper.h"
#include "cpu/reg.h"

#define instr pop

//#if DATA_BYTE == 2 || DATA_BYTE == 4
static void do_execute() {
	       OPERAND_W(op_dest,MEM_R(cpu.esp));
	       cpu.esp=cpu.esp+DATA_BYTE;
		print_asm_template1();
}
make_instr_helper(r)
make_instr_helper(rm)
//#if DATA_BYTE==2||DATA_BYTE==4
//make_instr_helper(si)
//#endif
#include "cpu/exec/template-end.h"

