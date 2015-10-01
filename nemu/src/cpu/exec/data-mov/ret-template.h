
#include "cpu/exec/template-start.h"
#include "cpu/exec/helper.h"
#include "cpu/reg.h"

#define instr ret
make_helper(concat(retnear_, SUFFIX))
{
//	   cpu.eip=MEM_R(cpu.esp);
	   cpu.eip=swaddr_read(cpu.esp,4);
//	   cpu.esp+=DATA_BYTE;
	   cpu.esp+=4;
//	   print_asm_template1();
	   print_asm("ret");
	   return 1;
}

#include "cpu/exec/template-end.h"

