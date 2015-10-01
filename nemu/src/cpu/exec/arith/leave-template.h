#include "cpu/exec/template-start.h"
#include "cpu/exec/helper.h"
#include "cpu/reg.h"

#define instr leave
make_helper(concat(leave_, SUFFIX))
{
	cpu.esp=cpu.ebp;  
        
        if(DATA_BYTE==4)
	{
	   cpu.ebp=MEM_R(cpu.esp);
           cpu.esp+=4;
           print_asm_template1();
        }
       else if(DATA_BYTE==2)
       {	
	  cpu.ebp=MEM_R(cpu.esp);
          cpu.esp+=2; 
       	  print_asm_template1();
       }   
	       return 1;						         
}

#include "cpu/exec/template-end.h"

