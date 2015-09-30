
#include "cpu/exec/template-start.h"

#define instr movzx

static void do_execute() {
	if(DATA_BYTE==1)
	{
		OPERAND_W(op_dest,(op_src->val&0xff));
	}
	else if(DATA_BYTE==2)
	{

	        OPERAND_W(op_dest,(op_src->val&0x00ff));
        }
      else
     	 {     
	     OPERAND_W(op_dest, op_src->val);
         }
	/* There is no need to update EFLAGS, since no other instructions 
	 * in PA will test the flags updated by this instruction.
	 */

	print_asm_template2();
}

make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
