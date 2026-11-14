# TV5 – GIAO DIỆN CONSOLE VÀ KIỂM THỬ TÍCH HỢP

## 1. Phạm vi phụ trách
Module `UserInterface` thực hiện phần giao diện console của QuizApp theo yêu cầu TV5. Module nhận thao tác từ người dùng, hiển thị dữ liệu và gọi các chức năng của `ExamSession`; không tự đọc file câu hỏi hoặc tự tính điểm.

## 2. Các file bàn giao
| File | Chức năng |
|---|---|
| `ConsoleUI.h` | Khai báo các chức năng giao diện |
| `ConsoleUI.cpp` | Menu, nhập thí sinh, màn hình làm bài, Dashboard, nộp bài và kết quả |
| `DisplayHelper.h` | Khai báo hàm hiển thị dùng chung |
| `DisplayHelper.cpp` | Kẻ đường phân cách, tiêu đề, thanh tiến độ, xử lý chuỗi và định dạng thời gian |
| `TestCases.md` | Danh sách trường hợp kiểm thử và kết quả mong đợi |
| `DemoScript.md` | Kịch bản trình diễn các chức năng |
| `README.md` | Hướng dẫn sử dụng và mô tả module |

## 3. Các màn hình
1. **Menu chính:** bắt đầu bài thi, giới thiệu chương trình, thoát.
2. **Thông tin thí sinh:** nhập họ tên, mã số sinh viên và lớp; không chấp nhận trường rỗng.
3. **Làm bài:** hiển thị nội dung câu hỏi, đủ bốn phương án A/B/C/D, đáp án đã chọn và trạng thái câu hỏi.
4. **Tiến độ:** hiển thị số câu đã trả lời và phần trăm hoàn thành.
5. **Dashboard:** hiển thị trạng thái từng câu; cho phép chọn câu để xem/sửa, tìm câu chưa trả lời hoặc nộp bài.
6. **Kết quả:** hiển thị thông tin thí sinh, số câu đúng/sai/chưa trả lời và điểm.

## 4. Phím thao tác
| Phím | Chức năng |
|---|---|
| `A`, `B`, `C`, `D` | Chọn hoặc sửa đáp án |
| `N` | Chuyển đến câu tiếp theo |
| `P` | Quay về câu trước |
| `S` | Đánh dấu bỏ qua câu hiện tại và thử chuyển đến câu chưa trả lời tiếp theo |
| `V` | Mở Dashboard (dùng V để không trùng với đáp án D) |
| `M` | Mở xác nhận nộp bài |
| `Y` / `N` | Xác nhận / không xác nhận nộp bài ở màn hình xác nhận |

Trong Dashboard: `1` chọn câu theo số thứ tự, `2` tìm câu chưa trả lời tiếp theo, `3` quay lại câu đang xem, `4` mở xác nhận nộp bài.

## 5. Kết nối với các module khác
- `TextQuestionRepository` nạp dữ liệu câu hỏi và chuyển danh sách `Question` cho luồng ứng dụng.
- `QuizApp` tạo `ExamSession` từ danh sách câu hỏi, thông tin `Candidate` và chiến lược chấm điểm.
- `ConsoleUI` gọi các hàm của `ExamSession` để lưu đáp án, chuyển câu, đọc tiến độ và lấy kết quả.
- `ExamSession` sử dụng `IGradingStrategy` / `StandardGradingStrategy` để tính điểm.
- `DisplayHelper` chỉ hỗ trợ trình bày, không chứa nghiệp vụ thi hoặc chấm điểm.

## 6. Cách biên dịch và chạy
Thực hiện tại thư mục gốc của project:
```bash
cmake -S . -B build
cmake --build build
```
Chạy file thực thi được tạo trong thư mục `build` (tên file `quiz_app.exe` trên Windows hoặc `quiz_app` trên Linux/macOS). Đảm bảo `questions.txt` nằm tại thư mục làm việc khi chạy chương trình.

## 7. Kiểm thử
Xem `TestCases.md` để thực hiện kiểm thử menu, nhập liệu, hiển thị câu hỏi, thao tác đáp án, Dashboard, nộp bài và kết quả. Chạy kiểm thử tích hợp tự động ở thư mục gốc:
```bash
ctest --test-dir build --output-on-failure
```
Bộ kiểm thử tự động hiện kiểm tra phần repository, phiên thi và chấm điểm. Các thao tác giao diện console cần được chạy theo bảng test case và ghi nhận Pass/Fail khi demo thực tế.

## 8. Lưu ý kỹ thuật
Thời lượng phiên thi hiện được cấu hình ở `QuizApp` (mặc định 30 phút). Việc kiểm tra thời gian diễn ra khi luồng giao diện tiếp tục xử lý sau mỗi lần nhập; `std::getline` đang chờ bàn phím không bị tự động ngắt ngang khi hết giờ. Nếu yêu cầu môn học bắt buộc tự động khóa bàn phím đúng thời điểm hết giờ, cần bổ sung cơ chế nhập liệu bất đồng bộ/phụ thuộc hệ điều hành.
