# Module QuestionRepository (TV3 - Hoàng)

## 1. Danh sách file bàn giao
- `QuestionValidation.h` / `QuestionValidation.cpp`: Kiểm tra định dạng chuỗi, số nguyên dương ID, trùng lặp ID, nội dung câu hỏi, 4 lựa chọn và ký tự đáp án `{A, B, C, D}`.
- `QuestionRepository.h` / `QuestionRepository.cpp`: Khai báo lớp giao diện `IQuestionRepository` và lớp kế thừa `TextQuestionRepository`.
- `questions.txt`: Ngân hàng 10 câu hỏi mẫu chuẩn định dạng `ID|Nội dung|A|B|C|D|Đáp án đúng|Giải thích`.
- `README.md`: Tài liệu hướng dẫn sử dụng module.

## 2. Hướng dẫn tích hợp cho TV1 và TV4
```cpp
#include <iostream>
#include "QuestionRepository/QuestionRepository.h"

using namespace std;

int main() {
    IQuestionRepository* repo = new TextQuestionRepository("QuestionRepository/questions.txt");

    if (repo->loadQuestions()) {
        const vector<Question>& dsCauHoi = repo->getAllQuestions();
        cout << "So cau hoi hop le: " << dsCauHoi.size() << "\n";

        
        const Question* q = repo->findQuestionById(1);
        if (q != nullptr) {
            cout << *q;
            cout << "Giai thich: " << q->getExplanation() << "\n";
        }
    }

    delete repo;
    return 0;
}
---

## 3: Hướng dẫn chạy kiểm thử (Test) trên máy trước khi nộp

Trước khi đẩy code lên GitHub, bạn hãy tạo tạm một file **`test_tv3.cpp`** nằm ngay tại thư mục gốc `Project-OOP-QuizApp` (bên ngoài 2 thư mục `QuestionManagement` và `QuestionRepository`) để biên dịch và kiểm tra mọi tình huống lỗi:

```cpp
#include <iostream>
#include "QuestionRepository/QuestionRepository.h"

using namespace std;

int main() {
    cout << "=== KIEM THU MODULE QUESTION REPOSITORY (TV3) ===\n";

    //Test 1: File ko ton tai
    cout << "\n[Test 1] Mo file khong ton tai:\n";
    IQuestionRepository* badRepo = new TextQuestionRepository("khong_ton_tai.txt");
    if (!badRepo->loadQuestions()) {
        cout << "-> PASS: Da bat duoc loi khong tim thay file.\n";
    }
    delete badRepo;

    // Test 2: Nạp dữ liệu chuẩn từ questions.txt
    cout << "\n[Test 2] Nap du lieu tu QuestionRepository/questions.txt:\n";
    IQuestionRepository* repo = new TextQuestionRepository("QuestionRepository/questions.txt");
    if (repo->loadQuestions()) {
        const vector<Question>& list = repo->getAllQuestions();
        cout << "-> PASS: Da nap thanh cong " << list.size() << " cau hoi.\n";

        // Test 3: Tìm kiếm câu hỏi theo ID hợp lệ
        cout << "\n[Test 3] Tim kiem cau hoi ID = 2:\n";
        const Question* q2 = repo->findQuestionById(2);
        if (q2 != nullptr) {
            cout << *q2;
            cout << "Giai thich: " << q2->getExplanation() << "\n";
        }

        // Test 4: Tìm kiếm ID không tồn tại
        cout << "\n[Test 4] Tim kiem cau hoi ID = 999:\n";
        if (repo->findQuestionById(999) == nullptr) {
            cout << "-> PASS: Tra ve nullptr dung nhu ky vong.\n";
        }
    }
    delete repo;
    return 0;
}