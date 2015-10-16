
#include "cpu/exec/template-start.h"

#define if_exec() OPERAND_W(op_dest, op_src->val);

#define else_exec() ;

#define all_exec() static void do_execute() {\
				       if(CMOVFLAG) if_exec() else else_exec();\
					   print_asm_template2();\
				   }\
				   make_instr_helper(rm2r)
#define instr cmove
#define CMOVFLAG cpu.eflags.ZF == 1

all_exec();

#undef CMOVFLAG
#undef instr
#define instr cmovge
#define CMOVFLAG cpu.eflags.SF == cpu.eflags.OF

all_exec();
	
#undef CMOVFLAG
#undef instr
#define instr cmovns
#define CMOVFLAG cpu.eflags.SF == 0

all_exec();

#undef CMOVFLAG
#undef instr

#define instr cmovs
#define CMOVFLAG cpu.eflags.SF == 1

all_exec();

#undef CMOVFLAG
#undef instr

#include "cpu/exec/template-end.h"
