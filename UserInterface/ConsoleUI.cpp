#include "ConsoleUI.h"

#include <iomanip>
#include <iostream>
#include <string>

// Doc mot thong tin bat buoc; khong chap nhan chuoi rong.
std::string ConsoleUI::readNonEmpty(const std::string& prompt) const {
    std::string value;

    while (true) {
        std::cout << prompt;

        if (!std::getline(std::cin, value)) {
            return "";
        }

        value = DisplayHelper::trim(value);

        if (!value.empty()) {
            return value;
        }

        std::cout << "Thong tin khong duoc de trong. Vui long nhap lai.\n";
    }
}

// Hien thi menu chinh va tra ve lua chon cua nguoi dung.
int ConsoleUI::showMainMenu() const {
    DisplayHelper::printTitle("QUIZ APPLICATION - MENU CHINH");

    std::cout << "1. Bat dau bai thi\n";
    std::cout << "2. Gioi thieu chuong trinh\n";
    std::cout << "3. Thoat chuong trinh\n";

    DisplayHelper::printLine('-');
    std::cout << "Lua chon (1-3): ";

    std::string choice;

    if (!std::getline(std::cin, choice)) {
        return 3;
    }

    choice = DisplayHelper::trim(choice);

    if (choice == "1") {
        return 1;
    }

    if (choice == "2") {
        return 2;
    }

    if (choice == "3") {
        return 3;
    }

    std::cout << "Lua chon khong hop le. Vui long chon lai.\n\n";
    return 0;
}

// Nhap thong tin thi sinh va tao doi tuong Candidate.
Candidate ConsoleUI::inputCandidate() const {
    DisplayHelper::printTitle("NHAP THONG TIN THI SINH");

    const std::string fullName =
        readNonEmpty("Ho va ten: ");

    const std::string studentId =
        readNonEmpty("Ma so sinh vien: ");

    const std::string className =
        readNonEmpty("Lop: ");

    return Candidate(fullName, studentId, className);
}

// Hien thi cau hoi hien tai, bon phuong an va trang thai tra loi.
void ConsoleUI::showQuestion(const ExamSession& session) const {
    const int currentIndex = session.getCurrentIndex();
    const std::size_t index =
        static_cast<std::size_t>(currentIndex);

    const Question& question =
        session.getQuestions().at(index);

    DisplayHelper::printTitle("MAN HINH LAM BAI THI");

    std::cout << "Thi sinh: "
              << session.getCandidate().getFullName()
              << " | MSSV: "
              << session.getCandidate().getStudentId()
              << '\n';

    DisplayHelper::printProgress(
        session.getAnsweredCount(),
        static_cast<int>(session.getQuestions().size())
    );

    std::cout << "Thoi gian da lam: "
              << DisplayHelper::formatDuration(
                     session.getElapsedSeconds()
                 )
              << " | Thoi gian con lai: "
              << DisplayHelper::formatDuration(
                     session.getRemainingSeconds()
                 )
              << '\n';

    DisplayHelper::printLine('-');

    std::cout << "Cau hoi "
              << currentIndex + 1
              << "/"
              << session.getQuestions().size()
              << ": "
              << question.getContent()
              << "\n\n";

    const auto& options = question.getOptions();

    for (std::size_t i = 0; i < options.size(); ++i) {
        std::cout << static_cast<char>('A' + i)
                  << ". " << options[i] << '\n';
    }

    const char selectedAnswer = session.getAnswers()[index];

    if (selectedAnswer != '\0') {
        std::cout << "\nDap an da chon: "
                  << selectedAnswer
                  << " (co the nhap lai de sua)\n";
    }

    const ExamSession::Status status =
        session.getStatus(index);

    std::cout << "Trang thai: ";

    if (status == ExamSession::Status::Answered) {
        std::cout << "Da tra loi\n";
    } else if (status == ExamSession::Status::Skipped) {
        std::cout << "Da bo qua\n";
    } else {
        std::cout << "Chua tra loi\n";
    }

    std::cout << "\nCAC LENH:\n";
    std::cout << "A/B/C/D: Chon dap an\n";
    std::cout << "N: Cau tiep theo | P: Cau truoc\n";
    std::cout << "S: Bo qua cau | V: Mo Dashboard\n";
    std::cout << "M: Nop bai\n";
}

// Hien thi danh sach cau hoi va trang thai cua tung cau.
void ConsoleUI::showDashboard(const ExamSession& session) const {
    DisplayHelper::printTitle("DASHBOARD - TIEN DO BAI THI");

    const int totalQuestions =
        static_cast<int>(session.getQuestions().size());

    DisplayHelper::printProgress(
        session.getAnsweredCount(),
        totalQuestions
    );

    std::cout << "Da tra loi: "
              << session.getAnsweredCount()
              << " | Da bo qua: "
              << session.getSkippedCount()
              << " | Chua tra loi: "
              << session.getBlankCount() - session.getSkippedCount()
              << '\n';

    std::cout << "Thoi gian con lai: "
              << DisplayHelper::formatDuration(
                     session.getRemainingSeconds()
                 )
              << '\n';

    DisplayHelper::printLine('-');

    for (std::size_t i = 0; i < session.getQuestions().size(); ++i) {
        const ExamSession::Status status =
            session.getStatus(i);

        std::string statusText;

        if (status == ExamSession::Status::Answered) {
            statusText = "Da tra loi";
        } else if (status == ExamSession::Status::Skipped) {
            statusText = "Da bo qua";
        } else {
            statusText = "Chua tra loi";
        }

        std::cout << "Cau "
                  << std::setw(2) << i + 1
                  << ": " << statusText;

        const char answer = session.getAnswers()[i];

        if (answer != '\0') {
            std::cout << " | Dap an: " << answer;
        }

        if (static_cast<int>(i) == session.getCurrentIndex()) {
            std::cout << " <-- Dang xem";
        }

        std::cout << '\n';
    }

    DisplayHelper::printLine('-');

    std::cout << "1. Chon mot cau de xem hoac sua dap an\n";
    std::cout << "2. Tim cau chua tra loi tiep theo\n";
    std::cout << "3. Quay lai cau dang xem\n";
    std::cout << "4. Nop bai\n";
}

// Dieu khien luong lam bai va xu ly cac lenh tu ban phim.
void ConsoleUI::runExam(ExamSession& session) const {
    while (!session.isTimeExpired()) {
        showQuestion(session);

        std::cout << "\nLua chon cua ban: ";

        std::string command;

        if (!std::getline(std::cin, command)) {
            return;
        }

        command = DisplayHelper::toUpper(
            DisplayHelper::trim(command)
        );

        // Nguoi dung chon mot trong bon dap an.
        if (command.size() == 1 &&
            command[0] >= 'A' &&
            command[0] <= 'D') {

            session.submitAnswer(command[0]);

            std::cout << "Da luu dap an.\n";

            if (session.getCurrentIndex() + 1 <
                static_cast<int>(session.getQuestions().size())) {

                session.setCurrentIndex(
                    session.getCurrentIndex() + 1
                );
            } else {
                std::cout << "Ban dang o cau cuoi. "
                          << "Co the xem lai hoac nop bai.\n";
            }
        }

        // Chuyen den cau tiep theo.
        else if (command == "N") {
            if (!session.setCurrentIndex(
                    session.getCurrentIndex() + 1
                )) {
                std::cout << "Ban dang o cau cuoi.\n";
            }
        }

        // Quay lai cau truoc.
        else if (command == "P") {
            if (!session.setCurrentIndex(
                    session.getCurrentIndex() - 1
                )) {
                std::cout << "Ban dang o cau dau tien.\n";
            }
        }

        // Danh dau cau hien tai la bo qua.
        else if (command == "S") {
            if (!session.skipCurrent()) {
                std::cout << "Khong co cau chua tra loi tiep theo "
                          << "de chuyen den.\n";
            }
        }

        // Mo Dashboard de xem tien do va chon cau.
        else if (command == "V") {
            bool returnToExam = false;

            while (!returnToExam && !session.isTimeExpired()) {
                showDashboard(session);

                std::cout << "\nThao tac: ";

                std::string dashboardChoice;

                if (!std::getline(std::cin, dashboardChoice)) {
                    return;
                }

                dashboardChoice =
                    DisplayHelper::trim(dashboardChoice);

                // Chon cau hoi theo so thu tu.
                if (dashboardChoice == "1") {
                    std::cout << "Nhap so cau muon xem: ";

                    std::string questionNumber;

                    if (!std::getline(std::cin, questionNumber)) {
                        return;
                    }

                    try {
                        std::size_t charactersRead = 0;

                        const int selectedNumber =
                            std::stoi(questionNumber, &charactersRead);

                        if (charactersRead != questionNumber.size() ||
                            !session.setCurrentIndex(selectedNumber - 1)) {

                            std::cout << "So cau khong hop le.\n";
                        } else {
                            returnToExam = true;
                        }
                    } catch (...) {
                        std::cout << "Vui long nhap so nguyen hop le.\n";
                    }
                }

                // Tim cau chua tra loi gan nhat tiep theo.
                else if (dashboardChoice == "2") {
                    const int nextQuestion =
                        session.findNextUnanswered(true);

                    if (nextQuestion == -1) {
                        std::cout << "Tat ca cac cau da duoc tra loi.\n";
                    } else {
                        session.setCurrentIndex(nextQuestion);
                        returnToExam = true;
                    }
                }

                // Quay lai cau dang xem.
                else if (dashboardChoice == "3") {
                    returnToExam = true;
                }

                // Xac nhan nop bai tu Dashboard.
                else if (dashboardChoice == "4") {
                    std::cout << "Xac nhan nop bai? (Y/N): ";

                    std::string confirmation;

                    if (!std::getline(std::cin, confirmation)) {
                        return;
                    }

                    confirmation = DisplayHelper::toUpper(
                        DisplayHelper::trim(confirmation)
                    );

                    if (confirmation == "Y") {
                        return;
                    }
                } else {
                    std::cout << "Lua chon Dashboard khong hop le.\n";
                }
            }
        }

        // Xac nhan nop bai tu man hinh cau hoi.
        else if (command == "M") {
            std::cout << "Ban co chac chan muon nop bai? (Y/N): ";

            std::string confirmation;

            if (!std::getline(std::cin, confirmation)) {
                return;
            }

            confirmation = DisplayHelper::toUpper(
                DisplayHelper::trim(confirmation)
            );

            if (confirmation == "Y") {
                return;
            }
        }

        // Lenh khong hop le.
        else {
            std::cout << "Lenh khong hop le. "
                      << "Vui long nhap A/B/C/D, N, P, S, V hoac M.\n";
        }
    }

    std::cout << "Da het thoi gian lam bai.\n";
}

// Hien thi thong tin thi sinh va ket qua sau khi ket thuc bai thi.
void ConsoleUI::showResult(const ExamSession& session) const {
    DisplayHelper::printTitle("KET QUA BAI THI");

    const Candidate& candidate = session.getCandidate();

    std::cout << "Ho va ten: " << candidate.getFullName() << '\n';
    std::cout << "Ma so sinh vien: "
              << candidate.getStudentId() << '\n';
    std::cout << "Lop: " << candidate.getClassName() << '\n';

    DisplayHelper::printLine('-');

    std::cout << "Thoi diem bat dau: "
              << DisplayHelper::formatDateTime(
                     session.getStartWallTime()
                 )
              << '\n';

    std::cout << "Thoi gian da lam: "
              << DisplayHelper::formatDuration(
                     session.getElapsedSeconds()
                 )
              << '\n';

    std::cout << "Tong so cau: "
              << session.getQuestions().size() << '\n';

    std::cout << "So cau da tra loi: "
              << session.getAnsweredCount() << '\n';

    std::cout << "So cau dung: "
              << session.getCorrectCount() << '\n';

    std::cout << "So cau sai: "
              << session.getWrongCount() << '\n';

    std::cout << "So cau chua tra loi: "
              << session.getBlankCount() << '\n';

    std::cout << "Trong do so cau da bo qua: "
              << session.getSkippedCount() << '\n';

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Tong diem: "
              << session.getScore() << "/10\n";

    DisplayHelper::printLine();

    std::cout << "Nhan Enter de quay lai menu chinh...";
    std::string wait;
    std::getline(std::cin, wait);
}

// Gioi thieu ngan gon ve ung dung.
void ConsoleUI::showAbout() const {
    DisplayHelper::printTitle("GIOI THIEU CHUONG TRINH");

    std::cout << "QuizApp la ung dung trac nghiem viet bang C++17.\n";
    std::cout << "Chuong trinh ho tro nhap thong tin thi sinh, "
              << "lam bai, theo doi tien do va xem ket qua.\n";
    std::cout << "Du lieu cau hoi duoc nap tu file questions.txt.\n\n";
}

// Thong bao khi nguoi dung thoat chuong trinh.
void ConsoleUI::showGoodbye() const {
    std::cout << "\nCam on ban da su dung QuizApp. Tam biet!\n";
}

// Hien thi loi khi khong the nap du lieu cau hoi.
void ConsoleUI::showError(const std::string& message) const {
    std::cout << "\n[LOI] " << message << '\n';
    std::cout << "Vui long kiem tra file questions.txt va thu lai.\n";
}
