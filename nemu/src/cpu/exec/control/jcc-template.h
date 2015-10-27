#include "cpu/exec/helper.h"
#include "cpu/exec/template-start.h"

make_helper(concat(concat(concat(j, CC), _), SUFFIX)) {
 DATA_TYPE_S offset = instr_fetch(eip + 1, DATA_BYTE);
 swaddr_t eip_temp = cpu.eip;
 eip_temp += (int32_t)offset;
  #if DATA_BYTE == 2
     eip_temp &= 0x0000ffff;
  #endif
if (COND)
{
   cpu.eip = eip_temp;
}
 #if DATA_BYTE == 1
 print_asm("j" str(CC) " %x", eip_temp + 1 + DATA_BYTE);
#else
 print_asm("j" str(CC) " %x", eip_temp + 2 + DATA_BYTE);
#endif
return 1 + DATA_BYTE;
}

#if DATA_BYTE == 4

//extern char suffix;

make_helper(concat(concat(j, CC), _v)) {
#if SUFFIX == l  
	return concat(concat(j, CC), _l)(eip);
#else 
	return  concat(concat (j, CC), _w)(eip));
#endif 
// return (SUFFIX == l ? concat(concat(j, CC), _l)(eip) : concat(concat(j, CC), _w)(eip));
}

#endif

#include "cpu/exec/template-end.h"

