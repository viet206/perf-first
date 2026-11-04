#include "pf_VM.h"
#include <stdio.h>

int main(int argc,char** argv) {
	if ( argc < 2 ) {
		printf("Usage : %s [file]\n",argv[0]);
		return 1;
	}
	
    FILE *file = fopen(argv[1],"rb");
    if (file == NULL) return 1;
    static unsigned char buffer[512] = {0};
    size_t bytesRead = fread(buffer, 1,512, file);
    if (bytesRead == 0) return 2;
    fclose(file);

    ptr i;
    i.uc = buffer;
    vexec(i);
}
