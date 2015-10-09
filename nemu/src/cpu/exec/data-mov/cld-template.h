
#include "cpu/exec/template-start.h"
#include "cpu/exec/helper.h"
#include "cpu/reg.h"

#define instr cld
make_helper(concat(cld_, SUFFIX))
{
//	   cpu.eip=MEM_R(cpu.esp);
	  // cpu.eip=swaddr_read(cpu.esp,4);
//	   printf("%x\n",cpu.eip);
//	   cpu.esp+=DATA_BYTE;
	   cpu.eflags.DF=0;
//	   print_asm_template1();
	   print_asm("cld");
	   return 1;
}

#include "cpu/exec/template-end.h"

