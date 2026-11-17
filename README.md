# QuizApp – Ứng dụng thi trắc nghiệm 

Ứng dụng thi trắc nghiệm viết bằng **C++17** theo hướng đối tượng (OOP) và có dùng nhiều **STL container**.
Có **giao diện cửa sổ chạy trực tiếp trên Windows** (Win32 API, không cần trình duyệt), chia hai khu vực:

- **Sinh viên**: nhập thông tin cá nhân, **chọn bộ đề**, làm bài, xem kết quả và xem lại bài.
- **Giảng viên**: đăng nhập bằng mật khẩu, **tạo / sửa / xóa bộ đề**, xem kết quả thi của sinh viên, đổi mật khẩu.

Dự án còn một bản **console** (chạy được cả Windows và Linux) dùng chung phần logic.

---

## 1. Đối chiếu yêu cầu của đề

| Yêu cầu | Cách đáp ứng |
|---|---|
| Tải câu hỏi và đáp án từ file `.txt` | `TextQuestionRepository` đọc file bộ đề (`id\|câu hỏi\|A\|B\|C\|D\|đáp án\|giải thích`) |
| Hiển thị tổng số câu và thời gian làm bài | Thanh thông tin màn hình thi: "Câu x/N", đồng hồ **đếm ngược**, thời gian đã làm |
| Nhập thông tin cá nhân | Màn hình *Thông tin thí sinh*: họ tên, MSSV, lớp (kiểm tra không để trống) |
| Hiển thị câu hỏi, trả lời từng câu | 4 lựa chọn A–D, chọn bằng chuột |
| **Bỏ qua** câu và trả lời lại sau | Nút *Bỏ qua câu này*, nút *Tới câu chưa làm*, danh sách câu hỏi hiện trạng thái |
| **Chỉnh sửa** đáp án bất kỳ lúc nào | Chọn lại đáp án hoặc *Xóa đáp án* cho tới khi nộp bài |
| Hiển thị kết quả: thông tin thí sinh, giờ bắt đầu, tổng thời gian, số câu đúng, tổng điểm | Màn hình *Kết quả bài thi* (thang 10) + *Xem lại bài làm* kèm giải thích |
| **Sáng tạo: chọn bộ đề** | Mỗi bộ đề là một file trong thư mục `exams/`; sinh viên chọn bộ đề trước khi thi |
| **Sáng tạo: giảng viên tạo bộ đề** | Trình soạn bộ đề trong ứng dụng, lưu thành file `.txt`, sinh viên thi được ngay |
| Thêm: tự nộp khi hết giờ, lưu lịch sử kết quả | Đồng hồ 1 giây; ghi vào `results.txt`; giảng viên xem bảng kết quả + điểm trung bình |

---

## 2. Cách chạy (Windows) – làm theo thứ tự

> Gói này là **mã nguồn**, chưa có file `.exe`. Bạn cần biên dịch một lần (khoảng 1–2 phút).

### Bước 1. Cài công cụ (chỉ làm một lần)

1. **CMake** (3.16 trở lên): <https://cmake.org/download/> – khi cài, chọn **Add CMake to the system PATH**.
2. **Một trình biên dịch C++17**, chọn một trong hai:
   - **MinGW-w64** (gọn nhẹ): cài từ MSYS2 (<https://www.msys2.org/>) hoặc tải bản winlibs (<https://winlibs.com/>), rồi thêm thư mục `bin` của nó vào PATH. Kiểm tra: mở Command Prompt, gõ `g++ --version`.
   - **Visual Studio Build Tools** (workload *Desktop development with C++*). Khi dùng cách này, hãy mở **Developer Command Prompt for VS** để chạy `build.bat`.

### Bước 2. Biên dịch

Giải nén ZIP, rồi **nhấp đúp `build.bat`** (hoặc mở Command Prompt trong thư mục dự án và gõ `build.bat`).
Script tự phát hiện trình biên dịch, build, chạy bộ kiểm thử logic, và tạo thư mục `dist\`.

### Bước 3. Chạy

Mở **`dist\QuizApp.exe`**. Cùng thư mục có sẵn `exams\` (3 bộ đề mẫu).

- `dist\QuizAppConsole.exe`: bản console (tùy chọn).
- **Đừng chuyển riêng file `.exe` ra chỗ khác**: hãy giữ nguyên cả thư mục `dist` (cần `exams\` và file `.manifest`).

### Build thủ công (không dùng build.bat)

```bat
cmake -S . -B build-mingw -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build build-mingw
build-mingw\QuizApp.exe
```

Với Visual Studio: `-G "NMake Makefiles"` trong Developer Command Prompt, hoặc mở thư mục bằng Visual Studio / VS Code (CMake Tools) rồi chọn target `QuizApp`.

### Linux / macOS (chỉ có bản console và bộ kiểm thử)

```bash
cmake -S . -B build && cmake --build build
./build/QuizApp          # bản console
./build/QuizAppTests     # chạy kiểm thử, chạy tại thư mục gốc dự án
```

---

## 3. Hướng dẫn sử dụng

### 3.1. Sinh viên

1. Trang chủ → **SINH VIÊN – Làm bài thi**.
2. Nhập **Họ và tên, Mã số sinh viên, Lớp** (Enter để sang ô kế tiếp).
3. Chọn **Bộ đề thi** trong danh sách (hiện số câu và thời gian làm bài) → **Bắt đầu làm bài**. Đồng hồ chạy ngay khi bạn xác nhận.
4. Trong lúc thi:
   - Chọn đáp án A/B/C/D; đổi ý chỉ cần chọn lại, hoặc bấm **Xóa đáp án**.
   - **Câu trước / Câu sau** để di chuyển; **Bỏ qua câu này** để làm sau.
   - Bảng **Danh sách câu hỏi** bên phải cho biết `[A-D]` đã chọn, `(bỏ qua)`, `-` chưa làm; bấm vào để nhảy tới câu bất kỳ; **Tới câu chưa làm** nhảy tới câu còn thiếu.
   - **NỘP BÀI** (có xác nhận, và cảnh báo nếu còn câu chưa làm). **Hết giờ ứng dụng tự nộp.**
5. Màn hình kết quả hiện: thông tin thí sinh, bộ đề, giờ bắt đầu, tổng thời gian, số câu đúng, điểm (thang 10). **Xem lại bài làm** cho biết từng câu đúng/sai và giải thích.

### 3.2. Giảng viên

1. Trang chủ → **GIẢNG VIÊN – Quản lý bộ đề** → nhập mật khẩu.
   **Mật khẩu mặc định: `admin123`** (màn hình đăng nhập có nhắc khi chưa đổi). Hãy đổi ngay ở mục *Đổi mật khẩu* (tối thiểu 4 ký tự).
2. Màn hình quản lý có danh sách bộ đề và các nút:
   - **Tạo bộ đề mới / Sửa bộ đề đã chọn** (hoặc nhấp đúp vào dòng) / **Xóa bộ đề đã chọn**.
   - **Xem kết quả thi**: bảng tất cả bài đã nộp (mới nhất ở trên), tổng số bài và điểm trung bình.
   - **Đổi mật khẩu**, **Đăng xuất**.
3. **Soạn bộ đề**:
   - Nhập **Tên bộ đề** và **Thời gian (phút)** ở thanh trên.
   - Điền nội dung câu hỏi, 4 phương án A–D, chọn **đáp án đúng**, (tùy chọn) giải thích → **Lưu câu hỏi này**.
   - Bấm một câu trong danh sách bên trái để **sửa**; dùng **Xóa câu**, **Lên / Xuống** để sắp xếp.
   - Khi đủ câu, bấm **LƯU BỘ ĐỀ**. Sinh viên chọn được ngay, không cần khởi động lại.
   - Quy tắc kiểm tra: không để trống, 4 phương án không trùng nhau, phải chọn đáp án đúng, không dùng ký tự `|`, thời gian 1–300 phút, bộ đề cần ít nhất 1 câu.

---

## 4. Cấu trúc dự án (giữ nguyên kiến trúc module ban đầu)

```text
QuizApp/
├── CMakeLists.txt          # cấu hình build (thư viện quizcore + GUI + console + tests)
├── build.bat               # build trên Windows, tạo dist\
├── main.cpp                # điểm vào bản console
├── main_gui.cpp            # điểm vào bản cửa sổ (WinMain)
├── QuizApp.h / .cpp        # điều phối luồng bản console
├── AppConfig.h / .cpp      # đường dẫn thư mục bộ đề, results.txt, teacher.cfg
├── ManageQuestion/         # Person, Candidate, Teacher, Question, ExamDraft
├── QuestionRepository/     # IQuestionRepository, TextQuestionRepository, ExamCatalog, ExamWriter
│   ├── exams/              #   bộ đề mẫu (de_01..de_03)
│   └── questions.txt       #   file câu hỏi gốc (tương thích)
├── QuizSession/            # QuizSession (phiên thi, chấm điểm), ResultStore (lịch sử kết quả)
├── UserInterface/          # ConsoleUI, DisplayHelper + GuiApp/GuiStudent/GuiTeacher (Win32)
├── cmake/CopyIfMissing.cmake
└── tests/quiz_tests.cpp    # 149 kiểm tra tự động cho phần logic
```

**OOP**: kế thừa (`Candidate`, `Teacher` ← `Person`), đa hình/giao diện (`IQuestionRepository` với `TextQuestionRepository`; `Person` có hủy ảo), đóng gói (mỗi module một trách nhiệm; GUI chỉ gọi logic, không tự chấm điểm).
**STL**: `std::vector` (danh sách câu hỏi, bộ đề), `std::map` (đáp án/trạng thái từng câu), `std::array` (4 phương án), `std::unordered_set` (kiểm tra trùng), `std::filesystem` (quét thư mục bộ đề).

Tách lớp: phần logic nằm trong thư viện `quizcore` không phụ thuộc giao diện, nên bản console, bản cửa sổ và bộ kiểm thử dùng chung một mã nguồn.

---

## 5. Định dạng file bộ đề

Mỗi bộ đề là một file `.txt` UTF-8 trong thư mục `exams/`:

```text
# Đề 2 - STL Container
#TIME: 8
1|vector là gì?|Mảng động|Danh sách liên kết|Bảng băm|Cây|A|vector lưu phần tử liên tiếp trong bộ nhớ.
2|...|...|...|...|...|C|...
```

- Dòng `# tên` (dòng chú thích đầu tiên): tên hiển thị. Không có thì lấy theo tên file.
- Dòng `#TIME: n`: thời gian làm bài (phút). Không có thì dùng 60 giây × số câu.
- Mỗi câu một dòng 8 trường ngăn bởi `|`: `id|câu hỏi|A|B|C|D|đáp án (A-D)|giải thích`.
- Dòng bắt đầu bằng `#` là chú thích. Dòng lỗi bị bỏ qua; file không có câu hợp lệ sẽ không xuất hiện trong danh sách.
- Bạn có thể soạn bằng Notepad (lưu **UTF-8**) và chép vào `exams\`, hoặc dùng trình soạn của giảng viên trong ứng dụng.

## 6. Dữ liệu ứng dụng sinh ra (cạnh file `.exe`)

| File | Nội dung |
|---|---|
| `results.txt` | Mỗi bài nộp một dòng: `RESULT\|họ tên\|MSSV\|lớp\|bộ đề\|giờ bắt đầu\|số giây\|đúng\|tổng\|điểm` |
| `teacher.cfg` | Mật khẩu giảng viên đã băm (salt + hash). **Xóa file này để về lại `admin123`.** |
| `exams/` | Các bộ đề. Build lại **không ghi đè** bộ đề đã sửa; muốn khôi phục mẫu, xóa thư mục `exams` rồi chạy `build.bat`. |

## 7. Bản console (tùy chọn)

```text
QuizAppConsole                            # menu chọn bộ đề trong thư mục exams
QuizAppConsole <thư_mục|file.txt>         # chọn thư mục khác hoặc thi thẳng một bộ đề
QuizAppConsole <thư_mục|file> <giây/câu>  # ví dụ 2 giây/câu để thử việc tự nộp khi hết giờ
```

Trong console, đồng hồ chỉ được kiểm tra mỗi lần nhấn Enter (do nhập dòng chặn); bản cửa sổ có đồng hồ thời gian thực.

## 8. Kiểm thử

- Tự động: `QuizAppTests` (149 kiểm tra: mô hình bộ đề, mật khẩu, đọc/ghi file bộ đề, lưu kết quả, phiên thi, chấm điểm, hết giờ). Chạy ở thư mục gốc dự án. `build.bat` tự chạy giúp.
- Thủ công: xem `UserInterface/TestCases.md` (có bảng test giao diện cửa sổ) và `UserInterface/DemoScript.md` (kịch bản demo).

## 9. Xử lý lỗi thường gặp

| Hiện tượng | Cách xử lý |
|---|---|
| `build.bat` báo không thấy `cmake` / `g++` | Cài lại và đảm bảo đã thêm vào PATH; **đóng và mở lại** cửa sổ lệnh |
| Báo lỗi generator / cache khi cấu hình | Xóa thư mục `build-mingw` hoặc `build-msvc` rồi chạy lại |
| Chạy `.exe` báo thiếu DLL (MinGW) | Dùng `build.bat` (đã liên kết tĩnh); nếu tự build, giữ nguyên các cờ `-static` trong CMakeLists |
| Giao diện nút trông kiểu cũ | Thiếu file `QuizApp.exe.manifest` cạnh `.exe` – chỉ ảnh hưởng hình thức |
| Danh sách bộ đề trống | Kiểm tra thư mục `exams` nằm cạnh `.exe` và file `.txt` lưu UTF-8, đúng 8 trường/dòng |
| Quên mật khẩu giảng viên | Xóa `teacher.cfg` cạnh `.exe`, đăng nhập lại bằng `admin123` |
| Chữ tiếng Việt hiện lỗi trong file đề | Mở bằng Notepad và lưu lại với mã hóa **UTF-8** |

## 10. Giới hạn đã biết (trung thực)

- **Giao diện Win32 chưa được biên dịch và chạy thử thực tế bởi người viết** (môi trường soạn mã là Linux, không có `windows.h`). Mã giao diện chỉ được kiểm tra cú pháp bằng header giả lập; phần logic dùng chung thì đã build và kiểm thử đầy đủ. Vì vậy lần build đầu có thể xuất hiện lỗi nhỏ; hãy gửi nguyên văn thông báo lỗi để sửa.
- Mật khẩu giảng viên chỉ ở mức đồ án: băm có salt, lưu cục bộ, **không** chống được người có quyền sửa file trên máy. Sinh viên cũng có thể đọc file bộ đề (kèm đáp án) trong thư mục `exams`.
- Ứng dụng chạy trên một máy, chưa có mạng/cơ sở dữ liệu; `results.txt` là file văn bản.
- Giao diện cố định 1000×680 và dùng font Segoe UI của Windows.
