#ifndef CORE_RAW_MACHINE_VM
#define CORE_RAW_MACHINE_VM

#include "TRACE.h"

#define ENABLE_TRACE 1

#define __VERSION "0.0.3"

/* Công nhận 2 type trong CRM:
 * - (unsigned) int
 * - (unsigned) char
 *
 * Thống nhất kích thước Word
 * là 4 byte ( hỗ trợ 32/64 bit)
 *
 * dấu '_' để dành cho type
 * thống nhất Format :
 * [ 8 bit opcode ] [ 24 bit const data ]
 *
 * Fact về LE:
 * viết theo dạng : 0x[MSB][LSB]
 * máy hiểu : 0x[LSB][MSB]
 * nếu viết theo dạng , thì máy hiểu bằng cách
 * bóc từng byte dịch ngược từ LSB -> MSB
 *
 * Ví dụ :
 * _ viết : 0xAABBCCDD
 * - máy hiểu : 0xDDCCBBAA
 */

typedef enum {
	OP_PUSH,
	OP_DROP,
	OP_ADD,
	OP_SUB,
	OP_MUL,
	OP_DIV,
	OP_JNE,
	OP_EXIT = 0xFF
}opcode;

typedef unsigned int _u;
typedef unsigned char _uc;
typedef int _cell;
typedef char _c;

typedef union {
	_u* u;
	_uc* uc;
	_cell* cell;
	_c* c;
	char* s;
	unsigned char * us;
}ptr;

int jmp_main(ptr code);

#endif
