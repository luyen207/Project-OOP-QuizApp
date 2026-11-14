#pragma once
#include <iostream>
#include <string>
#include <array>
#include <unordered_set>
using namespace std;

class QuestionValidation {
public:
    
    QuestionValidation() = delete;
    static string trim(const string& str);
    static bool isValidIdFormat(const string& idStr);
    static bool isDuplicateId(int id, const unordered_set<int>& existingIds);
    static bool isValidContentAndOptions(const string& content, const array<string, 4>& options);
    static bool isValidAnswer(const string& answerStr);
};