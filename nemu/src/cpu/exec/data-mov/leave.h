 #define DATA_BYTE 4
#include "cpu/exec/helper.h"
#include "cpu/reg.h"
#include "cpu/exec/template-start.h" 
make_helper(leave)
{
//OPERAND_W(cpu.esp, reg_l[R_EBP]);
 cpu.esp= cpu.ebp;
 cpu.ebp=MEM_R(cpu.esp,SS);
 cpu.esp=cpu.esp+DATA_BYTE;
return 1;
}
#undef DATA_BYTE
#include "cpu/exec/template-end.h"
