#pragma once

#include "DisplayHelper.h"
#include "../Exam/ExamSession.h"

#include <string>

// ConsoleUI phu trach nhap/xuat va dieu huong cac man hinh cua QuizApp.
class ConsoleUI {
private:
    std::string readNonEmpty(const std::string& prompt) const;
    void showQuestion(const ExamSession& session) const;
    void showDashboard(const ExamSession& session) const;

public:
    int showMainMenu() const;
    Candidate inputCandidate() const;

    // Tra ve khi thi sinh nop bai, het thoi gian hoac ket thuc input.
    void runExam(ExamSession& session) const;

    void showResult(const ExamSession& session) const;
    void showAbout() const;
    void showGoodbye() const;
    void showError(const std::string& message) const;
};
