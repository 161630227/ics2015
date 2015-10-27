
#include "cpu/exec/template-start.h"
#include "cpu/exec/helper.h"
#include "cpu/reg.h"

#define instr pop

//#if DATA_BYTE == 2 || DATA_BYTE == 4
static void do_execute() {
  DATA_TYPE result = swaddr_read(cpu.esp, DATA_BYTE, SS);
  cpu.esp += DATA_BYTE;
  OPERAND_W(op_src, result);
  print_asm_template1();

}
make_instr_helper(r)
make_instr_helper(rm)
//#if DATA_BYTE==2||DATA_BYTE==4
//make_instr_helper(si)
//#endif
#include "cpu/exec/template-end.h"

