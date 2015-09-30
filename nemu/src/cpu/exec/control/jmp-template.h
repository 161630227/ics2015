#include "cpu/exec/helper.h"
#include "cpu/exec/template-start.h"
#include "cpu/decode/modrm.h"

make_helper(concat(jmp_rel_,SUFFIX))
{
   cpu.eip+=instr_fetch(eip+1,DATA_BYTE); 
   print_asm("jmp"  " $0x%x", cpu.eip+DATA_BYTE+1);
    return 1+DATA_BYTE;
}

#include "cpu/exec/template-end.h"

