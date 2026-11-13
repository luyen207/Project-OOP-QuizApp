README - Module QuestionManagement (TV2)
Tài liệu bàn giao module Quản lý dữ liệu câu hỏi và người dự thi.
 1. Danh sách file
- 'Question.h' / 'Question.cpp': Lớp đối tượng Câu hỏi.
- 'Person.h' / 'Person.cpp': Lớp cơ sở quản lý người dùng.
- 'Readme.md': Tài liệu hướng dẫn (file này).
2. Kiến thức áp dụng
- Chương 2 (Classes & Objects): Đóng gói dữ liệu (private/protected), hàm khởi tạo, Getter/Setter.
- Chương 3 (Operator Overloading): Nạp chồng toán tử '<<' cho lớp Question (in câu hỏi bằng 'cout << q;') và Person.
- Chương 4 (Inheritance): Sử dụng 'protected' trong lớp Person làm nền tảng cho kế thừa.
3. Các hàm hỗ trợ module khác
- 'isValid()': Kiểm tra câu hỏi hợp lệ (không trống, đáp án A/B/C/D). Trả về 'true'/'false'.
- 'checkAnswer(char userAnswer)': Nhận đáp án người dùng, tự động viết hoa và so sánh. Trả về 'true'/false'.
4. Hướng dẫn tích hợp cho TV3 (Đọc file .txt)
Dựa trên format: 'ID|Nội dung|A|B|C|D|Đáp án đúng|Giải thích'
```cpp
#include "Question.h"
#include <vector>
array<string, 4> dapAn = {chuoi_A, chuoi_B, chuoi_C, chuoi_D};
Question q(stoi(chuoi_ID), chuoi_NoiDung, dapan, chuoi_DapAnDung[0], chuoi_GiaiThich);
vector<Question> nganHang;
nganHang.push_back(q);