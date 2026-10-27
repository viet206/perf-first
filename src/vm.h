#ifndef NEO_RPN_VM
#define NEO_RPN_VM

#include "hal/hal.h"

#define __VERSION "0.0.2"

#define OP_PUSH 0x01
#define OP_DROP 0x02
#define OP_ADD  0x03
#define OP_SUB  0x04
#define OP_PRINT 0x05
#define OP_EXIT 0xFF

typedef unsigned char byte_t;
typedef unsigned long long reg_t;
typedef int cell_t;

typedef union {
	byte_t* s;
	reg_t* r;
	int* i;
}ptr_t;

int jmp_main(ptr_t code);

#endif
