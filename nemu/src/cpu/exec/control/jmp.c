#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "jmp-template.h"
#undef DATA_BYTE
#define DATA_BYTE 2
#include "jmp-template.h"
#undef DATA_BYTE
#define DATA_BYTE 4
#include "jmp-template.h"
#undef DATA_BYTE


make_helper(jmp_rel_v)
{
	    return ((instr_fetch(eip,1))==0xe9 ? jmp_rel_l(eip) : jmp_rel_b(eip));
}
make_helper_v(jmp_rm);

/*make_helper(jmp_rm32)
{
	     ModR_M m;
	     m.val=instr_fetch(eip+1,1);
             cpu.eip=reg_l(m.R_M);
	     print_asm("jmp *"  "%%%s", regsl[m.R_M]);
             return 0;
}
*/
