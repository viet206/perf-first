import sys
import struct
import re

# --- 1. ĐỊNH NGHĨA OPCODES & DICTIONARY ---
OP_PUSH  = 0x01
OP_DROP   = 0x02
OP_ADD   = 0x03
OP_SUB = 0x04
OP_PRINT = 0x05
OP_EXIT = 0xFF

TOKEN_MAP = {
    '+': OP_ADD,
    '-': OP_SUB,
    '.': OP_PRINT,
    'drop': OP_DROP
}


# --- 2. THỦ TỤC ASSEMBLER ---

def assemble_forth(source_code):
    #clear comment
    source_code = re.sub(r"<.*?>", "", source_code, flags=re.DOTALL)
    source_code = re.sub(r"-.*", "", source_code)
    
    tokens = source_code.split()
    bytecode = []
    
    for token in tokens:
        # Nếu là số nguyên (hỗ trợ cả số âm)
        if token.isdigit() or (token.startswith('-') and token[1:].isdigit()):
            bytecode.append(OP_PUSH)
            bytecode.append(int(token))
        # Nếu là từ lệnh có trong từ điển
        elif token in TOKEN_MAP:
            bytecode.append(TOKEN_MAP[token])
        else:
            print(f"[Cảnh báo] Token không rõ nghĩa: '{token}'")
            
    bytecode.append(OP_EXIT)
    return bytecode


# --- 3. HÀM CHÍNH (MAIN) ---

def main():
    if len(sys.argv) < 3:
        print("""
        NeoRPN Assembler
        
        Usage : neoc.py file output

        """)
        sys.exit(1)
        
    input_path, output_path = sys.argv[1], sys.argv[2]
    
    try:
        with open(input_path, 'r', encoding='utf-8') as f:
            source_code = f.read()
    except FileNotFoundError as err:
        print(err)
        sys.exit(1)
        
    bytecode = assemble_forth(source_code)
    
    with open(output_path, 'wb') as f:
        skip_next = False
        for i in range(len(bytecode)):
            if skip_next:
                skip_next = False
                continue
                
            val = bytecode[i]
            if val == OP_PUSH:
                f.write(struct.pack('<B', OP_PUSH))
                f.write(struct.pack('<i', bytecode[i + 1]))
                skip_next = True
            else:
                f.write(struct.pack('<B', val))
            
if __name__ == "__main__":
    main()
