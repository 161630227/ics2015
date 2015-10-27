
#include "cpu/exec/template-start.h"
#include "cpu/exec/helper.h"
#include "cpu/reg.h"

#define instr ret
static void do_execute() {
	       //OPERAND_W(op_src,MEM_R(cpu.esp));
	        cpu.eip=swaddr_read(cpu.esp,4,SS)-2;
	        cpu.esp+=4;
		cpu.esp+=op_src->val;
		print_asm_template1();
}
make_instr_helper(i)
make_helper(concat(retnear_, SUFFIX))
{
//	   cpu.eip=MEM_R(cpu.esp);
	   cpu.eip=swaddr_read(cpu.esp,4,CS);
//	   printf("%x\n",cpu.eip);
//	   cpu.esp+=DATA_BYTE;
	   cpu.esp+=4;
//	   print_asm_template1();
	   print_asm("ret");
	   return 1;
}

#include "cpu/exec/template-end.h"

