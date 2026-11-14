# DEMO SCRIPT – QUIZ APPLICATION (TV5)

## 1. Mục tiêu demo
Trình bày luồng sử dụng giao diện console: menu chính, nhập thông tin thí sinh, làm bài với bốn lựa chọn, theo dõi tiến độ, điều hướng, Dashboard, nộp bài và xem kết quả.

## 2. Chuẩn bị
- Biên dịch project theo hướng dẫn trong README gốc.
- Đặt `questions.txt` tại thư mục làm việc khi chạy `quiz_app`.
- Chạy chương trình và chuẩn bị thông tin thí sinh thử nghiệm.

## 3. Kịch bản thao tác

| Bước | Thao tác demo | Nội dung thuyết minh |
|---|---|---|
| 1 | Chạy `quiz_app` | Đây là ứng dụng QuizApp chạy trên console |
| 2 | Chọn `2` | Giới thiệu ngắn về chương trình |
| 3 | Chọn `1` | Bắt đầu bài thi và mở màn hình nhập thí sinh |
| 4 | Nhập họ tên, MSSV, lớp | Thông tin được dùng để tạo đối tượng Candidate |
| 5 | Quan sát câu hỏi đầu tiên | Giao diện hiển thị nội dung câu hỏi và bốn phương án A-D |
| 6 | Nhập một đáp án, ví dụ `A` | ExamSession nhận và lưu đáp án; thanh tiến độ được cập nhật |
| 7 | Nhập `P` để quay lại, chọn đáp án khác | Minh họa khả năng xem lại và sửa câu trả lời |
| 8 | Nhập `S` tại một câu chưa trả lời | Minh họa trạng thái bỏ qua câu |
| 9 | Nhập `V` | Dashboard hiển thị trạng thái các câu |
| 10 | Trong Dashboard chọn `1`, nhập số câu | Minh họa chọn câu bất kỳ để xem hoặc sửa |
| 11 | Nhập `M`, xác nhận `Y` | Nộp bài thi |
| 12 | Quan sát màn hình kết quả | Hiển thị số câu đúng, sai, chưa trả lời và điểm |
| 13 | Nhấn Enter, chọn `3` | Quay về menu và thoát chương trình |

## 4. Giải thích kết nối module
- `ConsoleUI`: tiếp nhận lựa chọn và hiển thị thông tin.
- `DisplayHelper`: hỗ trợ tiêu đề, đường phân cách, thanh tiến độ và định dạng thời gian.
- `Candidate`: lưu thông tin thí sinh.
- `ExamSession`: lưu danh sách câu hỏi, đáp án, trạng thái và tiến độ phiên thi.
- `TextQuestionRepository`: cung cấp dữ liệu câu hỏi đã đọc từ TXT.
- `StandardGradingStrategy`: thực hiện tính điểm theo chiến lược chấm điểm được giao diện gọi gián tiếp thông qua ExamSession.
- `QuizApp`: kết nối các thành phần và điều phối luồng chương trình.

## 5. Hình ảnh minh họa
Thư mục `screenshots/` chứa hình minh họa bố cục các màn hình. Khi nộp báo cáo hoặc thuyết trình, nên bổ sung ảnh chụp trực tiếp từ chương trình chạy trên máy để chứng minh kết quả thực tế; không ghi ảnh minh họa là ảnh chụp kiểm thử thật.
