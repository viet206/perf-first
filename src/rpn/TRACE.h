#ifndef CRM_RPN_TRACE_VM
#define CRM_RPN_TRACE_VM

// Format Trace [trace] | info

#if ENABLE_TRACE == 1

#include <stdio.h>

#define TRACE_BEFORE do { \
	printf("[trace_bef] | pc : %08x\n",(int)(code.s - point)); \
	printf("[trace_bef] | opcode : %02x\n",word & 0xFF); \
	printf("[trace_bef] | imm : %d\n",(word >> 8) & 0xFFFFFF); \
}while(0)

#define TRACE_AFTER do { \
	printf("[trace_aft] | sp : %d\n",sp)
}while(0)

#else

#define TRACE_BEFORE (void)0
#define TRACE_AFTER (void)0

#endif

#endif
