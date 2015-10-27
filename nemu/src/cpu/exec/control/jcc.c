#include "cpu/exec/helper.h"

#define FLAG(x) cpu.eflags.x

#define DATA_BYTE 1
#define CC a
#define COND !(FLAG(CF) || FLAG(ZF))
#include "jcc-template.h"
#undef COND
#undef CC

#define CC ae
#define COND !FLAG(CF)
#include "jcc-template.h"
#undef COND
#undef CC


#define CC b
#define COND FLAG(CF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC be
#define COND FLAG(CF)||FLAG(ZF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC c
#define COND FLAG(CF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC e
#define COND FLAG(ZF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC g
#define COND (!FLAG(ZF)) &&( FLAG(OF)==FLAG(SF))
#include "jcc-template.h"
#undef COND
#undef CC

#define CC ge
#define COND FLAG(SF)==FLAG(OF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC l
#define COND !(FLAG(SF) == FLAG(OF))
#include "jcc-template.h"
#undef COND
#undef CC

#define CC le
#define COND FLAG(ZF)||(FLAG(SF)!=FLAG(OF))
#include "jcc-template.h"
#undef COND
#undef CC
#define FLAG(x) cpu.eflags.x

#define CC ne
#define COND ! FLAG(ZF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC no
#define COND FLAG(OF)
#include "jcc-template.h"
#undef COND
#undef 	CC

#define FLAG(x) cpu.eflags.x

#define CC np
#define COND ! FLAG(PF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC ns
#define COND !(FLAG(SF)) 
#include "jcc-template.h"
#undef COND
#undef CC

#define CC o
#define COND FLAG(OF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC p
#define COND FLAG(ZF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC s
#define COND FLAG(SF)
#include "jcc-template.h"
#undef COND
#undef CC
#undef DATA_BYTE

#define DATA_BYTE 2
#define CC a
#define COND !(FLAG(CF) || FLAG(ZF))
#include "jcc-template.h"
#undef COND
#undef CC

#define CC ae
#define COND !(FLAG(CF))
#include "jcc-template.h"
#undef COND
#undef CC

#define CC b
#define COND  FLAG(CF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC be
#define COND FLAG(CF)||FLAG(ZF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC c
#define COND FLAG(CF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC e
#define COND FLAG(ZF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC g
#define COND (!FLAG(ZF)) &&( FLAG(OF)==FLAG(SF))
//#define COND !FLAG(ZF) &&( FLAG(OF)==FLAG(SF))
#include "jcc-template.h"
#undef COND
#undef CC

#define CC ge
#define COND FLAG(SF)==FLAG(OF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC l
#define COND !(FLAG(SF) == FLAG(OF))
#include "jcc-template.h"
#undef COND
#undef CC

#define CC le
#define COND FLAG(ZF)||(FLAG(SF)!=FLAG(OF))
#include "jcc-template.h"
#undef COND
#undef CC

#define FLAG(x) cpu.eflags.x

#define CC ne
#define COND ! FLAG(ZF)
#include "jcc-template.h"
#undef COND
#undef CC

#define FLAG(x) cpu.eflags.x

#define CC no
#define COND ! FLAG(OF)
#include "jcc-template.h"
#undef COND
#undef CC

#define FLAG(x) cpu.eflags.x

#define CC np
#define COND ! FLAG(PF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC ns
#define COND !(FLAG(SF)) 
#include "jcc-template.h"
#undef COND
#undef CC

#define CC o
#define COND FLAG(OF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC p
#define COND FLAG(ZF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC s
#define COND FLAG(SF)
#include "jcc-template.h"
#undef COND
#undef CC
#undef DATA_BYTE

#define DATA_BYTE 4
#define CC a
#define COND !(FLAG(CF) || FLAG(ZF))
#include "jcc-template.h"
#undef COND
#undef CC


#define CC be
#define COND FLAG(CF)||FLAG(ZF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC b
#define COND FLAG(CF) 
#include "jcc-template.h"
#undef COND
#undef CC


#define CC ae
#define COND !FLAG(CF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC c
#define COND FLAG(CF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC e
#define COND FLAG(ZF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC g
#define COND (!FLAG(ZF)) &&( FLAG(OF)==FLAG(SF))
//#define COND FLAG(ZF) &&( FLAG(OF)==FLAG(SF))
#include "jcc-template.h"
#undef COND
#undef CC

#define CC ge
#define COND FLAG(SF)==FLAG(OF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC l
#define COND !(FLAG(SF) == FLAG(OF))
#include "jcc-template.h"
#undef COND
#undef CC

#define CC le
#define COND FLAG(ZF)||(FLAG(SF)!=FLAG(OF))
#include "jcc-template.h"
#undef COND
#undef CC

#define FLAG(x) cpu.eflags.x

#define CC ne
#define COND ! FLAG(ZF)
#include "jcc-template.h"
#undef COND
#undef CC

#define FLAG(x) cpu.eflags.x

#define CC no
#define COND ! FLAG(OF)
#include "jcc-template.h"
#undef COND
#undef CC

#define FLAG(x) cpu.eflags.x

#define CC np
#define COND ! FLAG(PF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC ns
#define COND !(FLAG(SF)) 
#include "jcc-template.h"
#undef COND
#undef CC

#define CC o
#define COND FLAG(OF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC p
#define COND FLAG(ZF)
#include "jcc-template.h"
#undef COND
#undef CC
#define CC s
#define COND FLAG(SF)
#include "jcc-template.h"
#undef COND
#undef CC


