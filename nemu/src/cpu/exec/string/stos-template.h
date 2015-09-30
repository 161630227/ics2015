

#include "cpu/exec/template-start.h"

#define instr stos

make_helper(concat(stos_, SUFFIX)) {
	if(DATA_BYTE==1){
	DATA_TYPE index=cpu.eax&0xFF;
        
	MEM_W(cpu.edi,index);
	if(cpu.eflags.DF==0) cpu.edi+=DATA_BYTE;
	else cpu.edi-=DATA_BYTE;
	//  print_asm_template2();
//	return 1;
	}
	else if (DATA_BYTE==2)
	{
	   DATA_TYPE index=cpu.eax&0xFFFF;
           MEM_W(cpu.edi,index);
	   if(cpu.eflags.DF==0) cpu.edi+=DATA_BYTE;
	   else cpu.edi-=DATA_BYTE;
	 }
	  else
	{	
	   DATA_TYPE index =cpu.eax;
	   MEM_W(cpu.edi,index);
	   if(cpu.eflags.DF==0) cpu.edi+=DATA_BYTE;
	   else cpu.edi-=DATA_BYTE;
	 }
	print_asm_template2();
	return 1;
}


#include "cpu/exec/template-end.h"
