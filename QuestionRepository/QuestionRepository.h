#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "../QuestionManagement/Question.h"
using namespace std;

class IQuestionRepository {
public:
    
    virtual ~IQuestionRepository() = default;
    virtual bool loadQuestions() = 0;
    virtual const vector<Question>& getAllQuestions() const = 0;
    virtual const Question* findQuestionById(int id) const = 0;
};

class TextQuestionRepository : public IQuestionRepository {
private:
    string filePath;
    vector<Question> questions;

public:
    explicit TextQuestionRepository(const string& path);

    bool loadQuestions() override;
    const vector<Question>& getAllQuestions() const override;
    const Question* findQuestionById(int id) const override;
    size_t getTotalQuestions() const;
};