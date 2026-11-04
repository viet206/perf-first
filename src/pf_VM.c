#include "pf_VM.h"

#define GET_OPCODE word & 0xFF
#define GET_VALUE ( word >> 8 ) & 0xFF
#define DEF_OPCODE(label,code) \
label: { \
	code; \
	NEXT; \
}
#define NEXT word = *(++c.u) ; goto *table[GET_OPCODE];
#define __STACK_MATH(op) *(--stack) op##= GET_VALUE;

void vexec(ptr c) {

	const void* table[] = {
		[S_PUSH] = &&s_push,
		[S_DROP] = &&s_drop,
		[S_ADD] = &&s_add,
		[S_SUB] = &&s_sub,
		[EXIT] = &&exit
	};

	int cell[10];
	int* stack = &cell[0];
	unsigned int word;

	word = *c.u;
	goto *table[GET_OPCODE];

	DEF_OPCODE(s_push,*(++stack) = GET_VALUE;)
	DEF_OPCODE(s_drop,--stack);
	DEF_OPCODE(s_add,__STACK_MATH(+));
	DEF_OPCODE(s_sub,__STACK_MATH(-));
exit:
}
