import struct
import os

# 定义矩阵数据
rows = 3
cols = 3
matrix_data = [1, 2, 3, 4, 5, 6, 7, 8, 9]

# --- 确保目录存在 ---
output_dir = "inputs/test_read_matrix"
if not os.path.exists(output_dir):
    os.makedirs(output_dir)

file_path = os.path.join(output_dir, "test_input.bin")

# --- 以二进制写入模式 (wb) 打开文件 ---
with open(file_path, "wb") as f:
    # 首先写入行数和列数，每个都是4字节的小端序整数 ('<i')
    f.write(struct.pack("<i", rows))
    f.write(struct.pack("<i", cols))

    # 接着写入矩阵的所有元素
    for number in matrix_data:
        f.write(struct.pack("<i", number))

print(f"'{file_path}' has been created successfully.")