#include "QuizApp.h"
#include <iostream>

void QuizApp::run() {
    int choice;

    do {
        showMainMenu();

        std::cout << "Nhap lua chon: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            startExam();
            break;

        case 2:
            showInstructions();
            break;

        case 0:
            std::cout << "Ket thuc chuong trinh!\n";
            break;

        default:
            std::cout << "Lua chon khong hop le!\n";
        }

    } while (choice != 0);
}

void QuizApp::showMainMenu() {
    std::cout << "\n===== QUIZAPP =====\n";
    std::cout << "1. Bat dau thi\n";
    std::cout << "2. Huong dan\n";
    std::cout << "0. Thoat\n";
}

void QuizApp::startExam() {
    std::cout << "Chuc nang thi se duoc tich hop sau.\n";
}

void QuizApp::showInstructions() {
    std::cout << "Chon dap an A, B, C hoac D.\n";
}