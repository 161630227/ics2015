
#include "cpu/exec/template-start.h"
#include "cpu/exec/helper.h"
#include "cpu/reg.h"

#define instr ret
make_helper(concat(retnear_, SUFFIX))
{
	   cpu.eip=MEM_R(cpu.esp);
	   cpu.esp+=DATA_BYTE;

	   print_asm_template1();
           return 1+DATA_BYTE;
}

#include "cpu/exec/template-end.h"

