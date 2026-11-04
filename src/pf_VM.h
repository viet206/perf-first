#ifndef PERF_FIRST_VM
#define PERF_FIRST_VM

typedef enum {
	S_PUSH = 0x00,
	S_DROP = 0x01,
	S_ADD = 0x02,
	S_SUB = 0x03,
	PRINT = 0x04,
	JNE = 0x05,
	JEQ = 0x06,
	EXIT = 0xFF
}op;

typedef union {
	unsigned char* uc;
	char* s;
	unsigned int* u;
	int* i;
}ptr;

void vexec(ptr c);

#endif
