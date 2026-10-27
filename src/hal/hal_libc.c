#include "hal.h"
#include <stdio.h>
#include <stdlib.h>

void print(char* s) {
        puts(s);
}

int readln(char* buf,int size) {
        return *(int*) fgets(buf,size,stdin);
}

void put_int(int i) {
        printf("%d\n",i);
}

int main(int argc, char* argv[]) {
    // Kiểm tra xem đã truyền tên file bytecode vào tham số dòng lệnh chưa
    if (argc < 2) {
        puts(" NeoRPN Loader\n"
	     " Usage : nrpn file \n"
	    );
        return 1;
    }

    // 1. Mở file bytecode ở chế độ đọc nhị phân ("rb")
    FILE* file = fopen(argv[1], "rb");
    if (!file) {
        perror("Lỗi: Không thể mở file bytecode");
        return 1;
    }

    // 2. Lấy kích thước file để cấp phát đúng lượng bộ nhớ cần thiết
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    if (file_size <= 0) {
        fprintf(stderr, "Lỗi: File trống hoặc không đọc được kích thước file.\n");
        fclose(file);
        return 1;
    }

    // 3. Init bộ nhớ và đọc toàn bộ nội dung file vào vùng nhớ đó
    byte_t* memory = (byte_t*)malloc(file_size);
    if (memory == NULL) {
        fprintf(stderr, "Lỗi: Không thể cấp phát bộ nhớ cho bytecode!\n");
        fclose(file);
        return 1;
    }

    size_t bytes_read = fread(memory, 1, file_size, file);
    fclose(file); // Đọc xong đóng file luôn

    if (bytes_read != (size_t)file_size) {
        fprintf(stderr, "Lỗi: Đọc file không hoàn tất!\n");
        free(memory);
        return 1;
    }

    // 4. Tạo `ptr_t` trỏ tới vùng nhớ chứa bytecode vừa nạp
    ptr_t code;
    code.s = memory;

    int result = jmp_main(code);

    printf("Thực thi hoàn tất. jmp_main trả về: %d\n", result);

    free(memory);

    return 0;
}
