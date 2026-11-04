#include "pf_VM.h"
#include <stdio.h>

#define OP_PRINT printf("%d\n",*stack);
#define GET_OPCODE word & 0xFF
#define GET_VALUE ( word >> 8 ) & 0xFF
#define DEF_OPCODE(label,code) \
label: { \
	code; \
	NEXT; \
}
#define NEXT word = *(++c.u) ; goto *table[GET_OPCODE];
#define __STACK_MATH(op) *(--stack) op##= *(stack + 1);

/* 
 * Format jump : [jump] exit_jump 00 00 00 00 ...Bytecode...
 *							^		^
 *							|		|
 *						condition	condition true (1)
 *						false (0)
 */
#define __JUMP(op) \
	++c.u; \
	r0 = ( *(--stack) op##= *(++stack) ); \
	c.u += *(c.u + r0);

void vexec(ptr c) {

	static const void* table[] = {
		[S_PUSH] = &&s_push,
		[S_DROP] = &&s_drop,
		[S_ADD] = &&s_add,
		[S_SUB] = &&s_sub,
		[PRINT] = &&print,
		[JNE] = &&jne,
		[JEQ] = &&jeq,
		[EXIT] = &&exit
	};

	int cell[10];
	int* restrict stack = &cell[0];
	unsigned int word;
	int r0;

	word = *c.u;
	goto *table[GET_OPCODE];

	DEF_OPCODE(s_push,*(++stack) = GET_VALUE;)
	DEF_OPCODE(s_drop,--stack);
	DEF_OPCODE(s_add,__STACK_MATH(+));
	DEF_OPCODE(s_sub,__STACK_MATH(-));
	DEF_OPCODE(print,OP_PRINT);
	DEF_OPCODE(jne,__JUMP(!));
	DEF_OPCODE(jeq,__JUMP(=));
exit:
}
