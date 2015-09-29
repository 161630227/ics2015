 #define DATA_BYTE 4
 #undef DATA_BYTE
#include "cpu/exec/helper.h"
#include "cpu/reg.h"
 make_helper(leave)
{
//OPERAND_W(cpu.esp, reg_l[R_EBP]);
 cpu.esp= cpu.ebp;
 cpu.ebp=cpu.esp;
 cpu.esp=cpu.esp+4;
return 1;
}
