#ifndef PERF_FIRST_VM
#define PERF_FIRST_VM

typedef enum {
	S_PUSH,
	S_DROP,
	S_ADD,
	S_SUB,
	EXIT
}op;

typedef union {
	unsigned char* uc;
	char* s;
	unsigned int* u;
	int* i;
}ptr;

void vexec(ptr c);

#endif
