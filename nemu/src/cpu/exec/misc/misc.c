#include "cpu/exec/helper.h"
#include "cpu/decode/modrm.h"
//#include "cpu/exec/esc_instr.h"
make_helper(nop) {
	print_asm("nop");
	return 1;
}

make_helper(int3) {
	void do_int3();
	do_int3();
	print_asm("int3");

	return 1;
}
/*make_heler(_2byte_esc){

	int instr_len=0;
	switch(instr_fetch(eip+1,1)){
	
		case 0x97: instr_len=seta(eip+1); break;
	        case 0x93: instr_len=setae(eip+1);break;
	        case 0x92: instr_len=setb(eip+1);break;
	        default: instr_len=inv(eip);break;        
	}
     return 1+instr_len;

}*/
make_helper(lea) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	int len = load_addr(eip + 1, &m, op_src);
	reg_l(m.reg) = op_src->addr;

	print_asm("leal %s,%%%s", op_src->str, regsl[m.reg]);
	return 1 + len;
}
