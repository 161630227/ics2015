#include "cpu/exec/template-start.h"

//#include "cpu/decode/modrm.h"
#define instr movzx
static void do_execute(){
//       printf("****");
	DATA_TYPE index=op_src->val;
     //  if(DATA_BYTE==2)index&=0x00ff;
      // if(DATA_BYTE==4)index&=0x0000ffff;       
	OPERAND_W(op_dest,index);
}
make_helper(concat(movzx_rmb2r_,SUFFIX)){
     //  printf("***\n");
	return idex(eip,decode_rm2r_b,concat(do_movzx_,SUFFIX));
}
#include "cpu/exec/template-end.h"
//make_helper(movsx_rmb2r_v);
//make_helper(movsx_rmw2r_v);


