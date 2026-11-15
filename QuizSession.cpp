#include "QuizSession.h"

#include <cctype>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <stdexcept>

QuizSession::QuizSession(const std::vector<Question>& questionList)
    : questions(questionList),
      currentIndex(0),
      started(false),
      submitted(false) {
    for (const auto& q : questions) {
        questionStatuses[q.getId()] = QuestionStatus::NOT_VISITED;
    }
}

bool QuizSession::isValidOption(char option, char& normalizedOut) {
    char upper = static_cast<char>(std::toupper(static_cast<unsigned char>(option)));
    if (upper == 'A' || upper == 'B' || upper == 'C' || upper == 'D') {
        normalizedOut = upper;
        return true;
    }
    return false;
}

std::string QuizSession::formatTimestamp(std::chrono::system_clock::time_point tp) {
    std::time_t rawTime = std::chrono::system_clock::to_time_t(tp);
    std::tm timeInfo{};
#ifdef _WIN32
    localtime_s(&timeInfo, &rawTime);
#else
    localtime_r(&rawTime, &timeInfo);
#endif
    std::ostringstream oss;
    oss << std::put_time(&timeInfo, "%d/%m/%Y %H:%M:%S");
    return oss.str();
}

std::string QuizSession::formatDurationMMSS(long long totalSeconds) {
    if (totalSeconds < 0) {
        totalSeconds = 0;
    }
    long long minutes = totalSeconds / 60;
    long long seconds = totalSeconds % 60;

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::setw(2) << std::setfill('0') << seconds;
    return oss.str();
}

// =========================================================================
// 1. QUẢN LÝ PHIÊN LÀM BÀI THI & THỜI GIAN
// =========================================================================

void QuizSession::startExam() {
    if (started) {
        return;
    }
    started = true;
    submitted = false;
    currentIndex = 0;
    startTimeFormatted = formatTimestamp(std::chrono::system_clock::now());
    examStartSteady = std::chrono::steady_clock::now();
}

void QuizSession::resetExam() {
    candidateAnswers.clear();
    questionStatuses.clear();
    for (const auto& q : questions) {
        questionStatuses[q.getId()] = QuestionStatus::NOT_VISITED;
    }
    currentIndex = 0;
    started = false;
    submitted = false;
    startTimeFormatted.clear();
    finalResult = ExamResult{};
}

bool QuizSession::isStarted() const {
    return started;
}

bool QuizSession::isSubmitted() const {
    return submitted;
}

std::string QuizSession::getStartTime() const {
    return startTimeFormatted;
}

long long QuizSession::getElapsedSeconds() const {
    if (!started) {
        return 0;
    }
    if (submitted) {
        return finalResult.durationSeconds;
    }
    auto now = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::seconds>(now - examStartSteady).count();
}

std::string QuizSession::getFormattedElapsedTime() const {
    return formatDurationMMSS(getElapsedSeconds());
}

// =========================================================================
// 2. ĐIỀU HƯỚNG CÂU HỎI (TIẾP THEO, CÂU TRƯỚC, NHẢY CÂU)
// =========================================================================

int QuizSession::getTotalQuestions() const {
    return static_cast<int>(questions.size());
}

int QuizSession::getCurrentIndex() const {
    return currentIndex;
}

const Question& QuizSession::getCurrentQuestion() const {
    if (questions.empty()) {
        throw std::out_of_range("Danh sach cau hoi dang rong.");
    }
    return questions[currentIndex];
}

const Question& QuizSession::getQuestionAt(int index) const {
    if (index < 0 || index >= getTotalQuestions()) {
        throw std::out_of_range("Chi so cau hoi nam ngoai pham vi hop le.");
    }
    return questions[index];
}

bool QuizSession::hasNextQuestion() const {
    return (currentIndex + 1) < getTotalQuestions();
}

bool QuizSession::hasPrevQuestion() const {
    return (currentIndex - 1) >= 0;
}

bool QuizSession::nextQuestion() {
    if (hasNextQuestion()) {
        ++currentIndex;
        return true;
    }
    return false;
}

bool QuizSession::prevQuestion() {
    if (hasPrevQuestion()) {
        --currentIndex;
        return true;
    }
    return false;
}

bool QuizSession::goToQuestion(int index) {
    if (index >= 0 && index < getTotalQuestions()) {
        currentIndex = index;
        return true;
    }
    return false;
}

bool QuizSession::goToQuestionById(int questionId) {
    for (int i = 0; i < getTotalQuestions(); ++i) {
        if (questions[i].getId() == questionId) {
            currentIndex = i;
            return true;
        }
    }
    return false;
}

// =========================================================================
// 3. LƯU ĐÁP ÁN, BỎ QUA & CHỈNH SỬA TRƯỚC KHI NỘP BÀI
// =========================================================================

bool QuizSession::answerCurrentQuestion(char option) {
    return updateAnswerByIndex(currentIndex, option);
}

bool QuizSession::updateAnswerByIndex(int index, char option) {
    // Khóa không cho chỉnh sửa nếu thí sinh đã nộp bài
    if (submitted || index < 0 || index >= getTotalQuestions()) {
        return false;
    }
    if (!started) {
        startExam();
    }

    char normalized = '\0';
    if (!isValidOption(option, normalized)) {
        return false;
    }

    int qId = questions[index].getId();
    candidateAnswers[qId] = normalized;
    questionStatuses[qId] = QuestionStatus::ANSWERED;
    return true;
}

bool QuizSession::updateAnswerById(int questionId, char option) {
    if (submitted) {
        return false;
    }
    char normalized = '\0';
    if (!isValidOption(option, normalized)) {
        return false;
    }

    for (int i = 0; i < getTotalQuestions(); ++i) {
        if (questions[i].getId() == questionId) {
            if (!started) {
                startExam();
            }
            candidateAnswers[questionId] = normalized;
            questionStatuses[questionId] = QuestionStatus::ANSWERED;
            return true;
        }
    }
    return false;
}

bool QuizSession::clearAnswerByIndex(int index) {
    if (submitted || index < 0 || index >= getTotalQuestions()) {
        return false;
    }
    int qId = questions[index].getId();
    candidateAnswers.erase(qId);
    questionStatuses[qId] = QuestionStatus::NOT_VISITED;
    return true;
}

bool QuizSession::skipCurrentQuestion() {
    if (!skipQuestionByIndex(currentIndex)) {
        return false;
    }
    // Tự động chuyển sang câu kế tiếp nếu chưa ở cuối danh sách
    if (hasNextQuestion()) {
        ++currentIndex;
    }
    return true;
}

bool QuizSession::skipQuestionByIndex(int index) {
    if (submitted || index < 0 || index >= getTotalQuestions()) {
        return false;
    }
    if (!started) {
        startExam();
    }

    int qId = questions[index].getId();
    candidateAnswers.erase(qId);
    questionStatuses[qId] = QuestionStatus::SKIPPED;
    return true;
}

// =========================================================================
// 4. TRUY VẤN TIẾN ĐỘ LÀM BÀI (CUNG CẤP CHO TV5 - PHÁT HIỂN THỊ)
// =========================================================================

char QuizSession::getAnswerByIndex(int index) const {
    if (index < 0 || index >= getTotalQuestions()) {
        return '\0';
    }
    int qId = questions[index].getId();
    auto it = candidateAnswers.find(qId);
    return (it != candidateAnswers.end()) ? it->second : '\0';
}

QuestionStatus QuizSession::getStatusByIndex(int index) const {
    if (index < 0 || index >= getTotalQuestions()) {
        return QuestionStatus::NOT_VISITED;
    }
    int qId = questions[index].getId();
    auto it = questionStatuses.find(qId);
    return (it != questionStatuses.end()) ? it->second : QuestionStatus::NOT_VISITED;
}

int QuizSession::getAnsweredCount() const {
    return static_cast<int>(candidateAnswers.size());
}

int QuizSession::getSkippedCount() const {
    int count = 0;
    for (const auto& entry : questionStatuses) {
        if (entry.second == QuestionStatus::SKIPPED) {
            ++count;
        }
    }
    return count;
}

int QuizSession::getUnansweredCount() const {
    return getTotalQuestions() - getAnsweredCount();
}

std::vector<int> QuizSession::getSkippedQuestionIndices() const {
    std::vector<int> indices;
    for (int i = 0; i < getTotalQuestions(); ++i) {
        if (getStatusByIndex(i) == QuestionStatus::SKIPPED) {
            indices.push_back(i);
        }
    }
    return indices;
}

std::vector<int> QuizSession::getUnansweredQuestionIndices() const {
    std::vector<int> indices;
    for (int i = 0; i < getTotalQuestions(); ++i) {
        if (getAnswerByIndex(i) == '\0') {
            indices.push_back(i);
        }
    }
    return indices;
}

// =========================================================================
// 5. NỘP BÀI, CHẤM ĐIỂM & XUẤT KẾT QUẢ CHO TV5
// =========================================================================

ExamResult QuizSession::submitExam(double maxScore) {
    if (submitted) {
        return finalResult;
    }
    if (!started) {
        startExam();
    }

    long long elapsed = getElapsedSeconds();
    submitted = true;

    ExamResult result;
    result.totalQuestions = getTotalQuestions();
    result.startTimeStr = startTimeFormatted;
    result.durationSeconds = elapsed;
    result.formattedDuration = formatDurationMMSS(elapsed);
    result.reviews.reserve(questions.size());

    int correct = 0;
    int wrong = 0;
    int unanswered = 0;

    for (const auto& q : questions) {
        int qId = q.getId();
        char correctOpt = static_cast<char>(
            std::toupper(static_cast<unsigned char>(q.getCorrectAnswer()))
        );

        QuestionReview rev;
        rev.questionId = qId;
        rev.correctAnswer = correctOpt;
        rev.status = questionStatuses[qId];

        auto ansIt = candidateAnswers.find(qId);
        if (ansIt == candidateAnswers.end()) {
            rev.userAnswer = '\0';
            rev.isCorrect = false;
            ++unanswered;
        } else {
            rev.userAnswer = ansIt->second;
            rev.isCorrect = (rev.userAnswer == correctOpt);
            if (rev.isCorrect) {
                ++correct;
            } else {
                ++wrong;
            }
        }
        result.reviews.push_back(rev);
    }

    result.correctCount = correct;
    result.wrongCount = wrong;
    result.unansweredCount = unanswered;

    if (result.totalQuestions > 0) {
        double rawScore = (static_cast<double>(correct) / result.totalQuestions) * maxScore;
        result.score = std::round(rawScore * 100.0) / 100.0;
        result.percentage = std::round((static_cast<double>(correct) / result.totalQuestions) * 10000.0) / 100.0;
    } else {
        result.score = 0.0;
        result.percentage = 0.0;
    }

    finalResult = result;
    return finalResult;
}

ExamResult QuizSession::getResult() const {
    return finalResult;
}
