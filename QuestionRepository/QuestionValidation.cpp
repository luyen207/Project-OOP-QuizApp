#include "QuestionValidation.h"
#include <cctype>

using namespace std;

string QuestionValidation::trim(const string& str) {
    const string whitespace = " \t\r\n";
    size_t first = str.find_first_not_of(whitespace);
    if (first == string::npos) {
        return "";
    }
    size_t last = str.find_last_not_of(whitespace);
    return str.substr(first, last - first + 1);
}

bool QuestionValidation::isValidIdFormat(const string& idStr) {
    if (idStr.empty()) {
        return false;
    }
    for (char c : idStr) {
        if (!isdigit(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    try {
        int id = stoi(idStr);
        return id > 0;
    } catch (...) {
        return false;
    }
}

bool QuestionValidation::isDuplicateId(int id, const unordered_set<int>& existingIds) {
    return existingIds.find(id) != existingIds.end();
}

bool QuestionValidation::isValidContentAndOptions(const string& content, const array<string, 4>& options) {
    if (content.empty()) {
        return false;
    }
    for (const auto& opt : options) {
        if (opt.empty()) {
            return false;
        }
    }
    return true;
}

bool QuestionValidation::isValidAnswer(const string& answerStr) {
    if (answerStr.length() != 1) {
        return false;
    }
    char c = static_cast<char>(toupper(static_cast<unsigned char>(answerStr[0])));
    return (c == 'A' || c == 'B' || c == 'C' || c == 'D');
}