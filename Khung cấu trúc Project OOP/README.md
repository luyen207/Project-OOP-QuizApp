# README – TV1: XÂY DỰNG KHUNG CHƯƠNG TRÌNH QUIZAPP

## 1. Giới thiệu

Trong dự án QuizApp, TV1 đảm nhiệm việc xây dựng khung chương trình ban đầu, tổ chức cấu trúc mã nguồn và thiết lập môi trường biên dịch cho ứng dụng.

Phần công việc này tạo nền tảng để phát triển chương trình, đảm bảo ứng dụng có điểm khởi chạy, lớp điều khiển chính và cấu hình biên dịch thống nhất.

## 2. Mục tiêu thực hiện

- Xây dựng cấu trúc thư mục cho dự án QuizApp.
- Tạo các file khởi chạy và điều khiển chương trình.
- Xây dựng menu chính và luồng hoạt động ban đầu.
- Thiết lập môi trường biên dịch bằng CMake.
- Đảm bảo chương trình có thể biên dịch và chạy bộ khung ban đầu.
- Chuẩn bị cấu trúc để tiếp nhận và tích hợp các phần chức năng sau này.

## 3. Cấu trúc file

Phần công việc của TV1 gồm các file sau:

```text
Integration/
├── main.cpp
├── QuizApp.h
├── QuizApp.cpp
└── CMakeLists.txt
```

## 4. Nội dung thực hiện

### 4.1. File main.cpp

File `main.cpp` là điểm bắt đầu thực thi chương trình.

Các công việc thực hiện:
- Khởi tạo đối tượng thuộc lớp `QuizApp`.
- Gọi phương thức `run()` để bắt đầu chương trình.
- Sử dụng cấu trúc `try-catch` để xử lý ngoại lệ.
- Hiển thị thông báo lỗi nếu chương trình xảy ra sự cố.

### 4.2. File QuizApp.h

File `QuizApp.h` dùng để khai báo lớp `QuizApp`, đóng vai trò điều khiển hoạt động chính của ứng dụng.

Các phương thức được khai báo:

| Phương thức | Chức năng |
|---|---|
| `run()` | Điều khiển luồng hoạt động của ứng dụng |
| `showMainMenu()` | Hiển thị menu chính |
| `startExam()` | Xử lý chức năng bắt đầu làm bài thi |
| `showInstructions()` | Hiển thị hướng dẫn sử dụng |

### 4.3. File QuizApp.cpp

File `QuizApp.cpp` triển khai các phương thức đã khai báo trong `QuizApp.h`.

Các công việc thực hiện:
- Xây dựng chức năng hiển thị menu chính.
- Nhận lựa chọn từ người dùng.
- Xử lý lựa chọn bắt đầu làm bài thi.
- Hiển thị hướng dẫn sử dụng.
- Xử lý lựa chọn thoát chương trình.
- Kiểm tra và thông báo khi người dùng nhập lựa chọn không hợp lệ.

### 4.4. File CMakeLists.txt

File `CMakeLists.txt` dùng để cấu hình và quản lý quá trình biên dịch dự án.

Các công việc thực hiện:
- Khai báo tên dự án là `QuizApp`.
- Thiết lập tiêu chuẩn ngôn ngữ C++17.
- Khai báo các file mã nguồn cần biên dịch.
- Khai báo đường dẫn đến các thư mục chứa file header.
- Chuẩn bị cấu hình để bổ sung các file mã nguồn khi tích hợp chương trình.

## 5. Công nghệ sử dụng

- Ngôn ngữ lập trình: C++.
- Tiêu chuẩn ngôn ngữ: C++17.
- Phương pháp lập trình: Lập trình hướng đối tượng (OOP).
- Công cụ quản lý biên dịch: CMake.
- Trình biên dịch: GCC, MinGW hoặc trình biên dịch tương thích C++17.

## 6. Hướng dẫn biên dịch và chạy chương trình

Mở terminal tại thư mục chứa file `CMakeLists.txt`.

**Bước 1: Tạo thư mục build**

```bash
cmake -S . -B build
```

**Bước 2: Biên dịch chương trình**

```bash
cmake --build build
```

**Bước 3: Chạy chương trình**

Trên Windows, nếu sử dụng cấu hình MinGW hoặc sinh file thực thi trực tiếp trong thư mục build:

```bash
.\build\QuizApp.exe
```

Trên Linux/macOS:

```bash
./build/QuizApp
```

Lưu ý: Đường dẫn file thực thi có thể thay đổi tùy theo trình biên dịch và cấu hình CMake.

## 7. Kết quả thực hiện

Sau khi hoàn thành phần nhiệm vụ, TV1 cần đạt được các kết quả:

- Xây dựng được bộ khung ban đầu của dự án QuizApp.
- Có file `main.cpp` để khởi chạy chương trình.
- Có lớp `QuizApp` để điều khiển hoạt động chính.
- Có menu chính và các chức năng điều hướng ban đầu.
- Có file `CMakeLists.txt` để cấu hình biên dịch.
- Có cấu trúc mã nguồn rõ ràng, thuận tiện cho việc phát triển và tích hợp.

## 8. Sản phẩm bàn giao

| STT | Tên file | Nội dung bàn giao |
|---|---|---|
| 1 | `main.cpp` | File khởi chạy chương trình |
| 2 | `QuizApp.h` | File khai báo lớp điều khiển chính |
| 3 | `QuizApp.cpp` | File triển khai các phương thức của lớp QuizApp |
| 4 | `CMakeLists.txt` | File cấu hình biên dịch |
| 5 | `README.md` | Tài liệu mô tả phần nhiệm vụ TV1 |

## 9. Kết luận

TV1 đã thực hiện xây dựng nền tảng ban đầu cho dự án QuizApp thông qua việc tổ chức cấu trúc thư mục, tạo file khởi chạy, xây dựng lớp điều khiển chính và thiết lập cấu hình biên dịch.

Đây là cơ sở để phát triển, kết nối và hoàn thiện các chức năng của hệ thống QuizApp trong những giai đoạn tiếp theo.