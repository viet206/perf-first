#ifndef NEO_RPN_VM
#define NEO_RPN_VM

typedef unsigned char byte_t;
typedef unsigned long long reg_t;

typedef union {
	byte_t* b;
	reg_t* r;
	int* i;
}ptr_t;

typedef struct {
	enum {
		INT,
		STRING,
		UINT
	}tag;
	union {
		int i;
		char* s;
		unsigned int ui;
	};
}cell_t;

int jmp_main(ptr_t code);

#endif
