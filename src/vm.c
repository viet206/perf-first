#include "vm.h"

#define NEXT \
        ++code.s; \
        goto *opcode[*code.s];

#define math(op) \
        if (sp < 1) return 0; \
        cell[sp - 1] op cell[sp]; \
        --sp;

int jmp_main(ptr_t code) {
        cell_t cell[5] = {0};
        int sp = -1;

        const void* opcode[] = {
                [OP_PUSH] = &&op_push,
                [OP_DROP] = &&op_drop,
                [OP_ADD]  = &&op_add,
                [OP_SUB]  = &&op_sub,
		[OP_PRINT] = &&op_print,
                [OP_EXIT] = &&op_exit
        };

        // Kick off the threaded interpreter loop
        goto *opcode[*code.s];

op_push:
        if (sp >= 4) return 0; // Stack overflow check
        ++sp;
        ++code.s;
        cell[sp] = *code.i;
	code.s += 3;
        NEXT

op_drop:
        if (sp < 0) return 0;  // Stack underflow check
        --sp;
        NEXT

op_add:
        math(+=)
        NEXT

op_sub:
        math(-=)
        NEXT
op_print:
	put_int(cell[sp]);
	NEXT
op_exit:
	if (sp < 0) return 0;
        return cell[sp];
}
