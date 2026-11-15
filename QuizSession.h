#pragma once

#include <chrono>
#include <map>
#include <string>
#include <vector>

// Tự động tìm file Question.h từ thư mục QuestionManagement của TV2 (Châu)
#if __has_include("Question.h")
    #include "Question.h"
#elif __has_include("../QuestionManagement/Question.h")
    #include "../QuestionManagement/Question.h"
#else
    #error "Khong tim thay file Question.h trong thu muc QuestionManagement!"
#endif

// Trạng thái của từng câu hỏi trong phiên làm bài
enum class QuestionStatus {
    NOT_VISITED, // Chưa xem tới
    SKIPPED,     // Đã xem nhưng chọn bỏ qua để làm sau
    ANSWERED     // Đã chọn đáp án
};

// Chi tiết kết quả từng câu hỏi (hỗ trợ TV5 hiển thị xem lại bài làm)
struct QuestionReview {
    int questionId = 0;
    char userAnswer = '\0';      // '\0' nếu thí sinh bỏ trống
    char correctAnswer = '\0';
    bool isCorrect = false;
    QuestionStatus status = QuestionStatus::NOT_VISITED;
};

// Gói dữ liệu kết quả đầy đủ truyền sang cho TV5 (Phát) hiển thị màn hình kết quả
struct ExamResult {
    int totalQuestions = 0;
    int correctCount = 0;
    int wrongCount = 0;
    int unansweredCount = 0;
    double score = 0.0;            // Điểm quy đổi thang 10.0
    double percentage = 0.0;       // Tỷ lệ phần trăm câu đúng (0 - 100%)
    std::string startTimeStr;      // Thời điểm bắt đầu thi (dd/mm/yyyy HH:MM:SS)
    long long durationSeconds = 0; // Tổng thời gian làm bài tính bằng giây
    std::string formattedDuration; // Tổng thời gian định dạng MM:SS
    std::vector<QuestionReview> reviews;
};

class QuizSession {
private:
    std::vector<Question> questions;
    std::map<int, char> candidateAnswers;           // STL Map lưu [ID câu hỏi -> Đáp án chọn]
    std::map<int, QuestionStatus> questionStatuses; // STL Map lưu [ID câu hỏi -> Trạng thái]

    int currentIndex;
    bool started;
    bool submitted;

    std::string startTimeFormatted;
    std::chrono::steady_clock::time_point examStartSteady;
    ExamResult finalResult;

    // Các hàm tiện ích nội bộ
    static bool isValidOption(char option, char& normalizedOut);
    static std::string formatTimestamp(std::chrono::system_clock::time_point tp);
    static std::string formatDurationMMSS(long long totalSeconds);

public:
    explicit QuizSession(const std::vector<Question>& questionList);

    // =========================================================================
    // 1. QUẢN LÝ PHIÊN LÀM BÀI THI & THỜI GIAN
    // =========================================================================
    void startExam();
    void resetExam();
    bool isStarted() const;
    bool isSubmitted() const;
    std::string getStartTime() const;
    long long getElapsedSeconds() const;
    std::string getFormattedElapsedTime() const;

    // =========================================================================
    // 2. ĐIỀU HƯỚNG CÂU HỎI (TIẾP THEO, CÂU TRƯỚC, NHẢY CÂU)
    // =========================================================================
    int getTotalQuestions() const;
    int getCurrentIndex() const; // Chỉ số từ 0 đến totalQuestions - 1
    const Question& getCurrentQuestion() const;
    const Question& getQuestionAt(int index) const;

    bool hasNextQuestion() const;
    bool hasPrevQuestion() const;
    bool nextQuestion();
    bool prevQuestion();
    bool goToQuestion(int index);
    bool goToQuestionById(int questionId);

    // =========================================================================
    // 3. LƯU ĐÁP ÁN, BỎ QUA & CHỈNH SỬA TRƯỚC KHI NỘP BÀI
    // =========================================================================
    bool answerCurrentQuestion(char option);
    bool updateAnswerByIndex(int index, char option);
    bool updateAnswerById(int questionId, char option);
    bool clearAnswerByIndex(int index);

    bool skipCurrentQuestion();
    bool skipQuestionByIndex(int index);

    // =========================================================================
    // 4. TRUY VẤN TIẾN ĐỘ LÀM BÀI (CUNG CẤP CHO TV5 - PHÁT HIỂN THỊ)
    // =========================================================================
    char getAnswerByIndex(int index) const; // Trả về '\0' nếu chưa chọn đáp án
    QuestionStatus getStatusByIndex(int index) const;
    int getAnsweredCount() const;
    int getSkippedCount() const;
    int getUnansweredCount() const;
    std::vector<int> getSkippedQuestionIndices() const;
    std::vector<int> getUnansweredQuestionIndices() const;

    // =========================================================================
    // 5. NỘP BÀI, CHẤM ĐIỂM & XUẤT KẾT QUẢ CHO TV5
    // =========================================================================
    ExamResult submitExam(double maxScore = 10.0);
    ExamResult getResult() const;
};
