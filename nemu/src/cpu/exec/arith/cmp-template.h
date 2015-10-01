

#include "cpu/exec/template-start.h"

#define instr cmp
static void do_execute(){
	DATA_TYPE result = op_dest->val - op_src->val;
	

	/* TODO: Update EFLAGS. */
        DATA_TYPE_S index=result;
	printf("%d\n",index);
        cpu.eflags.CF=op_dest->val<op_src->val;
	cpu.eflags.ZF=(result==0);
	cpu.eflags.PF=1;
        cpu.eflags.SF=MSB(result);//index<0;
	printf("%x  %x\n",op_dest->val,op_src->val);
	while (index)
       {
	       if(index&0x1) cpu.eflags.PF=!cpu.eflags.PF;
	       index&=(index-1);
        }
        cpu.eflags.AF=(result^(op_dest->val))>>4;
//        cpu.eflags.OF=(((op_src->val<0)!=(op_dest->val<0))&&((op_dest->val<0)!=(result<0)));
	cpu.eflags.OF = (MSB(op_src->val)!=MSB(op_dest->val)&&(MSB(op_dest->val!=MSB(result))));
print_asm_template2();
}
make_instr_helper(i2rm)
make_instr_helper(r2rm)
make_instr_helper(i2a)
make_instr_helper(rm2r)
#if (DATA_BYTE == 2 || DATA_BYTE == 4)
make_instr_helper(si2rm)
#endif
#include "cpu/exec/template-end.h"
