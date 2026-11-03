#include "crm_vm.h"

#define FETCH \
        word = *(++code.u); \
        goto *table[word & 0xFF]

#define GET_OP word & 0xFF
#define GET_DAT ( word >> 8 ) & 0xFFFFFF

#define DEFINE_OP(name,handler) \
name: { \
	TRACE_BEFORE; \
	handler; \
	TRACE_AFTER; \
	FETCH; \
}

#define __math(opcode) \
	--sp; \
	cell[sp] opcode cell[sp + 1]

int jmp_main(ptr code) {
        _cell cell[128] = {0};
        int sp = -1;
        unsigned int word;

        int pre; // previous result
        int re; // result
        int op; // math op
        
        const void* table[] = {
                [OP_PUSH] = &&op_push,
                [OP_DROP] = &&op_drop,
                [OP_ADD] = &&op_add,
                [OP_SUB] = &&op_sub,
                [0xFF] = &&op_exit
        };

        word = *code.u; 
        goto *table[word & 0xFF];

        DEFINE_OP(op_push,
        	++sp;
        	cell[sp] = GET_DAT
   		)

        DEFINE_OP(op_add,__math(+=))
        
        DEFINE_OP(op_sub,__math(-=))
        DEFINE_OP(op_drop,--sp)
op_exit:
	return cell[sp];
}
