#pragma once
#include <iostream>
#include <string>
#include <array>
using namespace std;
class Question {
private:
    int id;
    string content;
    array<string, 4> options; 
    char correctAnswer;
    string explanation;
public:
    Question(int _id = 0, string _content = "", array<string, 4> _options = {"", "", "", ""}, char _correct = 'A', string _explanation = "");
    int getId() const;
    void setId(int _id);
    string getContent() const;
    void setContent(string _content);
    array<string, 4> getOptions() const;
    void setOptions(array<string, 4> _options);
    char getCorrectAnswer() const;
    void setCorrectAnswer(char _correct);
    string getExplanation() const;
    void setExplanation(string _explanation);
    bool isValid() const;
    bool checkAnswer(char userAnswer) const;
    friend ostream& operator<<(ostream& out, const Question& q);
};