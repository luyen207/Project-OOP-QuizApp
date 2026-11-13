# QUIZAPP – HỆ THỐNG THI TRẮC NGHIỆM

## 1. Giới thiệu dự án

QuizApp là chương trình thi trắc nghiệm được xây dựng bằng ngôn ngữ C++, phục vụ việc tổ chức và thực hiện các bài kiểm tra trắc nghiệm trên môi trường console.

Chương trình cho phép người dự thi nhập thông tin cá nhân, làm bài với các câu hỏi được lưu trữ trong tệp dữ liệu, lựa chọn hoặc thay đổi đáp án trước khi nộp bài và xem kết quả sau khi hoàn thành.

Dự án được thực hiện trong khuôn khổ môn học **Cấu trúc dữ liệu và giải thuật**, nhằm vận dụng kiến thức lập trình C++, lập trình hướng đối tượng và các cấu trúc dữ liệu phù hợp vào một ứng dụng thực tế.

## 2. Mục tiêu dự án

- Xây dựng chương trình thi trắc nghiệm bằng C++.
- Áp dụng lập trình hướng đối tượng để tổ chức và quản lý dữ liệu.
- Sử dụng các cấu trúc dữ liệu phù hợp để lưu trữ danh sách câu hỏi và câu trả lời.
- Xây dựng chức năng đọc dữ liệu câu hỏi từ tệp TXT.
- Xử lý quá trình làm bài và chấm điểm tự động.
- Tổ chức chương trình thành các module riêng biệt để thuận tiện phát triển, kiểm thử và bảo trì.

## 3. Chức năng chính

### 3.1. Quản lý thông tin người dự thi
- Nhập thông tin người dự thi.
- Khởi tạo đối tượng người dự thi.
- Lưu trữ thông tin phục vụ quá trình làm bài.

### 3.2. Quản lý câu hỏi
- Lưu trữ nội dung câu hỏi.
- Mỗi câu hỏi có bốn phương án lựa chọn A, B, C, D.
- Lưu đáp án đúng và phần giải thích cho câu hỏi.
- Kiểm tra tính hợp lệ của dữ liệu câu hỏi.

### 3.3. Đọc dữ liệu câu hỏi
- Đọc danh sách câu hỏi từ tệp TXT.
- Chuyển dữ liệu đọc được thành các đối tượng câu hỏi.
- Kiểm tra dữ liệu đầu vào.
- Xử lý trường hợp tệp không tồn tại, tệp rỗng hoặc dữ liệu không hợp lệ.

### 3.4. Tổ chức bài thi
- Bắt đầu phiên làm bài.
- Hiển thị lần lượt các câu hỏi và phương án trả lời.
- Lưu đáp án do người dự thi lựa chọn.
- Cho phép chuyển đến câu tiếp theo hoặc quay lại câu trước.
- Cho phép bỏ qua câu hỏi.
- Cho phép thay đổi đáp án trước khi nộp bài.

### 3.5. Chấm điểm và hiển thị kết quả
- Đối chiếu đáp án của người dự thi với đáp án đúng.
- Tính số câu trả lời đúng.
- Tính số câu trả lời sai.
- Tính số câu chưa trả lời.
- Tính điểm bài thi theo thang điểm 10.
- Hiển thị kết quả sau khi nộp bài.

Công thức tính điểm:

Điểm = (Số câu đúng / Tổng số câu hỏi) × 10

## 4. Công nghệ sử dụng

| Thành phần | Công nghệ |
|---|---|
| Ngôn ngữ lập trình | C++ |
| Chuẩn ngôn ngữ | C++17 |
| Mô hình lập trình | Lập trình hướng đối tượng (OOP) |
| Lưu trữ câu hỏi | Tệp văn bản TXT |
| Lưu trữ kết quả | CSV (nếu triển khai chức năng lịch sử kết quả) |
| Công cụ quản lý biên dịch | CMake |
| Cấu trúc dữ liệu | STL và các cấu trúc phù hợp với từng module |

## 5. Cấu trúc thư mục dự án

```text
QuizApp/
│
├── QuestionManagement/
│   ├── Question.h
│   ├── Question.cpp
│   ├── Person.h
│   ├── Person.cpp
│   └── README.md
│
├── QuestionRepository/
│   ├── QuestionRepository.h
│   ├── QuestionRepository.cpp
│   ├── QuestionValidation.h
│   ├── QuestionValidation.cpp
│   └── README.md
│
├── ExamProcessing/
│   ├── ExamSession.h
│   ├── ExamSession.cpp
│   ├── GradingStrategy.h
│   ├── GradingStrategy.cpp
│   ├── TestCases.md
│   ├── TestReport.md
│   └── README.md
│
├── UserInterface/
│   ├── ConsoleUI.h
│   ├── ConsoleUI.cpp
│   ├── DisplayHelper.h
│   ├── DisplayHelper.cpp
│   ├── TestCases.md
│   ├── DemoScript.md
│   └── README.md
│
├── Integration/
│   ├── main.cpp
│   ├── QuizApp.h
│   ├── QuizApp.cpp
│   └── CMakeLists.txt
│
├── data/
│   └── questions.txt
│
├── results/
│   └── history.csv
│
├── tests/
│   ├── test_question.cpp
│   ├── test_repository.cpp
│   ├── test_exam_session.cpp
│   └── test_grading.cpp
│
└── README.md
```

## 6. Định dạng dữ liệu câu hỏi

Dữ liệu câu hỏi được lưu trong tệp `data/questions.txt`.

Mỗi dòng tương ứng với một câu hỏi, các trường dữ liệu được phân cách bằng ký tự `|`.

Cấu trúc:

```text
ID|Question|A|B|C|D|Answer|Explanation
```

Ví dụ:

```text
Q001|C++ la gi?|Ngon ngu lap trinh|He dieu hanh|Trinh duyet|Co so du lieu|A|C++ la ngon ngu lap trinh.
Q002|Kieu du lieu so nguyen trong C++?|int|float|double|char|A|int dung de luu so nguyen.
Q003|Ham nao la diem bat dau cua chuong trinh C++?|start()|main()|run()|begin()|B|Ham main la diem bat dau cua chuong trinh C++.
```

Quy định:
- ID câu hỏi không được trùng lặp.
- Mỗi câu hỏi phải có đầy đủ nội dung và bốn phương án.
- Đáp án đúng phải thuộc một trong bốn lựa chọn A, B, C hoặc D.
- Các trường dữ liệu phải được phân cách đúng định dạng.

## 7. Hướng dẫn cài đặt và biên dịch

### 7.1. Yêu cầu môi trường

Cần chuẩn bị:
- Trình biên dịch hỗ trợ C++17, ví dụ GCC, MinGW hoặc MSVC.
- CMake phiên bản 3.16 trở lên.
- Visual Studio Code, Visual Studio hoặc IDE hỗ trợ C++.

### 7.2. Biên dịch bằng CMake

Mở terminal tại thư mục `Integration`:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

Sau khi biên dịch thành công, chương trình thực thi sẽ được tạo trong thư mục build.

### 7.3. Chạy chương trình

Trên Windows, có thể chạy:

```bash
QuizApp.exe
```

Trên Linux hoặc macOS, có thể chạy:

```bash
./QuizApp
```

Lưu ý: Tên và vị trí file thực thi có thể khác nhau tùy hệ điều hành và cấu hình CMake.

## 8. Quy trình hoạt động của chương trình

1. Khởi động ứng dụng QuizApp.
2. Đọc danh sách câu hỏi từ tệp dữ liệu.
3. Kiểm tra dữ liệu câu hỏi.
4. Nhập thông tin người dự thi.
5. Bắt đầu phiên làm bài.
6. Hiển thị câu hỏi và các phương án lựa chọn.
7. Người dự thi chọn, bỏ qua hoặc thay đổi đáp án.
8. Người dự thi nộp bài.
9. Hệ thống thực hiện chấm điểm.
10. Hiển thị kết quả bài thi.

## 9. Phân công thực hiện

| Thành viên | Module phụ trách | Nội dung chính |
|---|---|---|
| TV1 – Nhóm trưởng | Integration | Xây dựng kiến trúc, tạo chương trình chính, tích hợp các module và kiểm tra toàn hệ thống. |
| TV2 | QuestionManagement | Xây dựng class Question, Person và Candidate; quản lý dữ liệu câu hỏi và người dự thi. |
| TV3 | QuestionRepository | Đọc dữ liệu từ TXT, kiểm tra tính hợp lệ và tìm kiếm câu hỏi. |
| TV4 | ExamProcessing | Quản lý phiên làm bài, lưu đáp án và thực hiện chấm điểm. |
| TV5 | UserInterface | Xây dựng giao diện console, hiển thị câu hỏi, kết quả và hỗ trợ kiểm thử. |

## 10. Kiểm thử chương trình

Các module cần được kiểm thử độc lập trước khi tích hợp.

Một số trường hợp cần kiểm tra:

- Chương trình khởi động bình thường.
- Đọc được tệp câu hỏi hợp lệ.
- Xử lý tệp câu hỏi không tồn tại.
- Xử lý tệp dữ liệu rỗng.
- Phát hiện ID câu hỏi trùng lặp.
- Xử lý đáp án không hợp lệ.
- Lưu đúng câu trả lời của người dự thi.
- Cho phép thay đổi đáp án trước khi nộp bài.
- Tính điểm chính xác.
- Hiển thị đúng số câu đúng, sai và chưa trả lời.

Kết quả kiểm thử chi tiết được ghi nhận trong các tài liệu `TestCases.md` và `TestReport.md` của từng module.

## 11. Hướng phát triển

- Bổ sung chức năng quản lý ngân hàng câu hỏi.
- Bổ sung chức năng phân loại câu hỏi theo chủ đề và mức độ khó.
- Bổ sung chức năng trộn thứ tự câu hỏi và phương án trả lời.
- Bổ sung chức năng giới hạn thời gian làm bài.
- Lưu lịch sử kết quả của người dự thi.
- Cải thiện giao diện và trải nghiệm sử dụng.

## 12. Thông tin dự án

- **Tên dự án:** QuizApp – Hệ thống thi trắc nghiệm.
- **Ngôn ngữ:** C++17.
- **Môn học:** Lập trình hướng đối tượng OOP
- **Nhóm thực hiện:** [Group 10].


---

*README.md là tài liệu giới thiệu và hướng dẫn sử dụng dự án QuizApp. Nội dung cần được cập nhật tương ứng với phiên bản chương trình thực tế sau khi các module được hoàn thiện và tích hợp.*
