#include "QuestionRepository.h"
#include "QuestionValidation.h"
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <cctype>
using namespace std;
TextQuestionRepository::TextQuestionRepository(const string& path)
    : filePath(path) {}

bool TextQuestionRepository::loadQuestions() {
    questions.clear();

    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Khong the mo file du lieu: " << filePath << "\n";
        return false;
    }
    unordered_set<int> existingIds;
    string line;
    int lineNumber = 0;

    while (getline(file, line)) {
        lineNumber++;
        if (lineNumber == 1 && line.size() >= 3 &&
            static_cast<unsigned char>(line[0]) == 0xEF &&
            static_cast<unsigned char>(line[1]) == 0xBB &&
            static_cast<unsigned char>(line[2]) == 0xBF) {
            line.erase(0, 3);
        }

        string trimmedLine = QuestionValidation::trim(line);
        if (trimmedLine.empty()) {
            continue;
        }

        stringstream ss(trimmedLine);
        string token;
        vector<string> parts;
        parts.reserve(8);

        while (getline(ss, token, '|')) {
            parts.push_back(QuestionValidation::trim(token));
        }
        if (!trimmedLine.empty() && trimmedLine.back() == '|') {
            parts.push_back("");
        }

        if (parts.size() != 8) {
            cerr << " Dong " << lineNumber
                 << ": Sai cau truc (yeu cau du 8 truong ngan cach boi '|').\n";
            continue;
        }

        const string& idStr = parts[0];
        const string& content = parts[1];
        array<string, 4> options = { parts[2], parts[3], parts[4], parts[5] };
        const string& answerStr = parts[6];
        const string& explanation = parts[7];

        if (!QuestionValidation::isValidIdFormat(idStr)) {
            cerr << " Dong " << lineNumber
                 << ": ID khong hop le ('" << idStr << "').\n";
            continue;
        }
        int id = stoi(idStr);

       
        if (QuestionValidation::isDuplicateId(id, existingIds)) {
            cerr << " Dong " << lineNumber
                 << ": ID bi trung lap (" << id << ").\n";
            continue;
        }

        
        if (!QuestionValidation::isValidContentAndOptions(content, options)) {
            cerr << " Dong " << lineNumber
                 << " (ID " << id << "): Thieu noi dung cau hoi hoac phuong an lua chon.\n";
            continue;
        }

        
        if (!QuestionValidation::isValidAnswer(answerStr)) {
            cerr << " Dong " << lineNumber
                 << " (ID " << id << "): Dap an khong hop le ('" << answerStr << "').\n";
            continue;
        }

        char correctAns = static_cast<char>(toupper(static_cast<unsigned char>(answerStr[0])));

       
        Question q(id, content, options, correctAns, explanation);

       
        if (!q.isValid()) {
            cerr << " Dong " << lineNumber
                 << " (ID " << id << "): Du lieu khong dat chuan Question::isValid().\n";
            continue;
        }

        existingIds.insert(id);
        questions.push_back(q);
    }

    file.close();

    
    if (questions.empty()) {
        cerr << "File khong co cau hoi hop le nao de nap!\n";
        return false;
    }

    return true;
}

const vector<Question>& TextQuestionRepository::getAllQuestions() const {
    return questions;
}

const Question* TextQuestionRepository::findQuestionById(int id) const {
    for (const auto& q : questions) {
        if (q.getId() == id) {
            return &q;
        }
    }
    return nullptr;
}

size_t TextQuestionRepository::getTotalQuestions() const {
    return questions.size();
}
