#include "neorpn_vm.h"
#include <stdio.h>

int main() {
	unsigned char c[] = {
		OP_PUSH,05,00,00,00,
		OP_PUSH,07,00,00,00,
		OP_ADD,
		OP_EXIT
	};

	ptr_t a;
	a.s = c;

	int n = jmp_main(a);

	printf("stat : %d\n",n);
}
