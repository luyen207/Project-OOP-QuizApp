#include "QuizApp.h"
#include <iostream>
#include <exception>

int main() {
    try {
        QuizApp app;
        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Loi: " << e.what() << '\n';
        return 1;
    }

    return 0;
}