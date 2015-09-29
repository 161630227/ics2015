
#include "cpu/exec/template-start.h"

#define instr movs

/*static void do_execute() {
	OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}*/
make_helper(concat(movb_, SUFFIX)) {
   //	swaddr_t addr = instr_fetch(eip + 1, 4);
    //	MEM_W(addr, REG(R_EAX));
	DATA_TYPE index=op_src->val;
	int incdec;
	OPERAND_W(op_dest,index);
	if(cpu.eflags.DF==0)incdec=1;
	else incdec=-1;	
	cpu.esi+=incdec;
	cpu.edi+=incdec;
        print_asm_template2();
	return 1;
}

make_helper(concat(movv_, SUFFIX)) {
//	swaddr_t addr = instr_fetch(eip + 1, 4);
	DATA_TYPE index=op_src->val;
	int incdec;
	OPERAND_W(op_dest,index);
	if (cpu.eflags.DF==0&&DATA_BYTE==1) incdec=2;
	else if(cpu.eflags.DF==0&&DATA_BYTE==2)incdec=4;
	else if (cpu.eflags.DF==1&&DATA_BYTE==1)incdec=-2;
	else incdec=-4;
        cpu.esi+=incdec;
	cpu.edi+=incdec;

        print_asm_template2();
	return 5;
}

#include "cpu/exec/template-end.h"
