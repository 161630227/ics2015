
#include "cpu/exec/template-start.h"

#define instr movs
make_helper(concat(movb_, SUFFIX)) {
	DATA_TYPE index=MEM_R(cpu.esi);
	int incdec;
	MEM_W(cpu.edi,index);
	if(cpu.eflags.DF==0)incdec=DATA_BYTE;
	else incdec=-DATA_BYTE;	
	cpu.esi+=incdec;
	cpu.edi+=incdec;
        print_asm_template2();
	return 1;
}

make_helper(concat(movv_, SUFFIX)) {
//	swaddr_t addr = instr_fetch(eip + 1, 4);
	DATA_TYPE index=MEM_R(cpu.esi);
	MEM_W(cpu.edi,index);
	int incdec;
/*	if (cpu.eflags.DF==0&&DATA_BYTE==1) incdec=2;
	else if(cpu.eflags.DF==0&&DATA_BYTE==2)incdec=4;
	else if (cpu.eflags.DF==1&&DATA_BYTE==1)incdec=-2;
	else incdec=-4;
  */
	if(cpu.eflags.DF==0)incdec=DATA_BYTE;
	else incdec=-DATA_BYTE;	
  	cpu.esi+=incdec;
	cpu.edi+=incdec;

        print_asm_template2();
	return 5;
}

#include "cpu/exec/template-end.h"
