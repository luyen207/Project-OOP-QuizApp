# TEST CASES – TV5: GIAO DIỆN CONSOLE VÀ KIỂM THỬ TÍCH HỢP

## A. Kiểm thử giao diện thủ công

| ID | Chức năng | Dữ liệu / thao tác | Kết quả mong đợi |
|---|---|---|---|
| TC01 | Menu chính | Chạy chương trình | Hiện 3 lựa chọn: bắt đầu, giới thiệu, thoát |
| TC02 | Kiểm tra menu | Nhập `9` hoặc chữ bất kỳ | Báo lựa chọn không hợp lệ và hiển thị lại menu |
| TC03 | Giới thiệu | Chọn `2` | Hiện mô tả QuizApp, sau đó quay lại menu |
| TC04 | Bắt đầu thi | Chọn `1` | Chuyển đến màn hình nhập thông tin thí sinh |
| TC05 | Kiểm tra dữ liệu rỗng | Để trống họ tên/MSSV/lớp | Yêu cầu nhập lại, không tạo thí sinh với trường rỗng |
| TC06 | Nhập thí sinh | Nhập họ tên, MSSV, lớp hợp lệ | Tạo Candidate và bắt đầu phiên thi |
| TC07 | Hiển thị câu hỏi | Bắt đầu bài thi | Có nội dung câu hỏi và đủ 4 phương án A/B/C/D |
| TC08 | Chọn đáp án | Nhập `A`, `B`, `C` hoặc `D` | Đáp án được lưu; tiến độ được cập nhật |
| TC09 | Sửa đáp án | Quay lại câu đã trả lời và nhập đáp án khác | Đáp án mới thay đáp án cũ |
| TC10 | Câu tiếp theo | Nhập `N` | Chuyển sang câu tiếp theo nếu còn câu |
| TC11 | Câu trước | Nhập `P` | Chuyển về câu trước nếu không ở câu đầu |
| TC12 | Bỏ qua | Nhập `S` tại câu chưa trả lời | Câu được đánh dấu bỏ qua; chương trình thử chuyển tới câu chưa trả lời tiếp theo |
| TC13 | Mở Dashboard | Nhập `V` | Hiện danh sách câu và trạng thái từng câu |
| TC14 | Chọn câu trên Dashboard | Chọn `1`, nhập số câu hợp lệ | Mở đúng câu để xem hoặc sửa đáp án |
| TC15 | Tìm câu chưa trả lời | Trong Dashboard chọn `2` | Chuyển đến câu chưa trả lời tiếp theo nếu còn |
| TC16 | Quay lại từ Dashboard | Trong Dashboard chọn `3` | Trở về câu đang xem trước đó |
| TC17 | Nộp bài | Nhập `M`, sau đó xác nhận `Y` | Kết thúc phần làm bài và hiển thị kết quả |
| TC18 | Hủy nộp bài | Nhập `M`, sau đó nhập `N` | Không nộp bài; tiếp tục làm bài |
| TC19 | Kết quả | Hoàn thành hoặc nộp bài | Hiện thí sinh, tổng câu, đúng, sai, chưa trả lời và điểm |
| TC20 | Thoát | Tại menu chọn `3` | Hiện lời chào tạm biệt và kết thúc chương trình |
| TC21 | Thiếu file câu hỏi | Đổi tên hoặc di chuyển `questions.txt` rồi bắt đầu thi | Hiện thông báo lỗi đọc file, không bắt đầu phiên thi |

## B. Kiểm thử tích hợp tự động
Chạy tại thư mục gốc:
```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Bộ `integration_tests` hiện kiểm tra:
- Đọc dữ liệu câu hỏi từ file TXT.
- Mỗi câu có bốn phương án.
- Tạo phiên thi và trạng thái ban đầu.
- Lưu và sửa đáp án.
- Tính số câu đúng/sai và điểm.
- Chặn chỉ số câu ngoài phạm vi và ký tự đáp án không hợp lệ.

**Lưu ý:** kiểm thử tự động hiện tập trung vào repository, phiên thi và chấm điểm; các thao tác console trong phần A cần được người thực hiện chạy trực tiếp và ghi nhận kết quả.

## C. Bảng ghi nhận khi chạy thực tế
Điền cột kết quả sau khi chạy trên máy demo:

| ID | Kết quả thực tế (Pass/Fail) | Ghi chú |
|---|---|---|
| TC01–TC21 | Nhóm tự ghi nhận | Ghi lỗi nếu kết quả khác mong đợi |
