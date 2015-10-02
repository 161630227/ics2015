#include "cpu/exec/template-start.h"

//#include "cpu/decode/modrm.h"
#define instr movsx
static void do_execute(){
	printf("%x\n",op_dest->val);
	DATA_TYPE_S index=op_src->val;
	index=(index<<(DATA_BYTE*8-8)>>(DATA_BYTE*8-8));
	OPERAND_W(op_dest,index);
}
make_helper(concat(movsx_rmb2r_,SUFFIX)){
	return idex(cpu.eip,decode_rm2r_b,concat(do_movsx_,SUFFIX));
}
#include "cpu/exec/template-end.h"
//make_helper(movsx_rmb2r_v);
//make_helper(movsx_rmw2r_v);


