#include "neorpn_vm.h"

int jmp_main(ptr_t code) {
	cell_t cell[5] = {0};

	const void* jmp_table[] = {
		[OP_PUSH] = &&op_push,
		[OP_DROP] = &&op_drop,
		[OP_ADD] = &&op_add,
		[OP_SUB] = &&op_sub,
		[OP_PRINT] = &&op_print,
		[OP_EXIT] = &&op_exit
	};

op_exit:
	return;
}
