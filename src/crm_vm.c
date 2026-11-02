#include "crm_vm.h"

#define FETCH \
        word = *(++code.u); \
        goto *table[word & 0xFF]

#define GET_OP word & 0xFF
#define GET_DAT ( word >> 8 ) & 0xFFFFFF

#define DEFINE_OP(name,handler) \
name: { \
	handler; \
	FETCH; \
}

#define __math(op) \
	--sp; \
	cell[sp] op cell[sp + 1]

int jmp_main(ptr code) {
		// Init Memory VM
        _cell cell[5] = {0};
        int sp = -1;
        unsigned int word;
        
        const void* table[] = {
                [OP_PUSH] = &&op_push,
                [OP_DROP] = &&op_drop,
                [OP_ADD] = &&op_add,
                [OP_SUB] = &&op_sub,
                [OP_EXIT] = &&op_exit
        };

        word = *code.u; 
        goto *table[word & 0xFF];

        DEFINE_OP(op_push,
        	cell[++sp] = GET_DAT
        )

        DEFINE_OP(op_add,__math(+=))
        DEFINE_OP(op_sub,__math(-=))
        DEFINE_OP(op_drop,--sp)
op_exit:
	return cell[sp];
}
