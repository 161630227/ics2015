#include "cpu/exec/template-start.h"
#include "cpu/exec/helper.h"
#include "cpu/reg.h"

#define instr call

#if DATA_BYTE == 2 || DATA_BYTE == 4
static void do_execute() {
		cpu.esp=cpu.esp-4;
		swaddr_write(cpu.esp,4,cpu.eip);
		cpu.eip+=op_src->val;

					
		print_asm_template1();
}

make_instr_helper(i)
#endif
#include "cpu/exec/template-end.h"

