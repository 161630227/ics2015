
#include "cpu/exec/template-start.h"

#define instr cmps

make_helper(concat(cmps_, SUFFIX)) {
	DATA_TYPE index=MEM_R(cpu.esi,DS)-MEM_R(cpu.edi,ES);
	MEM_W(cpu.esi,index,DS);
	if(cpu.eflags.DF==0) cpu.esi+=DATA_BYTE;
	else cpu.esi-=DATA_BYTE;
	print_asm_template2();
	return 1;
}


#include "cpu/exec/template-end.h"
