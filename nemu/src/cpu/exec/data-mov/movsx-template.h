#include "cpu/exec/template-start.h"
#include "cpu/exec/helper.h"
#include "cpu/decode/modrm.h"
#define instr movsx
static void do_execute(){
	printf("%x\n",op_dest->val);
	DATA_TYPE_S index=op_src->val;
	index=(index<<(DATA_BYTE*8-8)>>(DATA_BYTE*8-8));
	OPERAND_W(op_dest,index);
        print_asm_template2();
}
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(rm_b2r)
#endif

#if DATA_BYTE == 4 
	make_instr_helper(rm_w2r)
#endif
#include "cpu/exec/template-end.h"
//make_helper(movsx_rmb2r_v);
//make_helper(movsx_rmw2r_v);


