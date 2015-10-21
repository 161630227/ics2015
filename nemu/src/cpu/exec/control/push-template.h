
#include "cpu/exec/template-start.h"
#include "cpu/exec/helper.h"
#include "cpu/reg.h"

#define instr push

//#if DATA_BYTE == 2 || DATA_BYTE == 4
static void do_execute() {
	      
          	
		if (DATA_BYTE==2)
		{
			cpu.esp-=2;
			MEM_W(cpu.esp,op_src->val,SS);
		}
		else
		{
			cpu.esp-=4;
//			printf("%x\n",op_src->val);
			swaddr_write(cpu.esp, 4, op_src->val,SS);
//			MEM_W(cpu.esp,op_src->val);
		         // swaddr_write(cpu.esp,4,op_src->val);
		} 			
		print_asm_template1();
}
make_instr_helper(r)
make_instr_helper(rm)
make_instr_helper(i)
//#if DATA_BYTE==2||DATA_BYTE==4
//make_instr_helper(si)
//#endif
#include "cpu/exec/template-end.h"

