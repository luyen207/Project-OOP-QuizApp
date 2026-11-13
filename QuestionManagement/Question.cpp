#include "Question.h"
#include <cctype> 
Question::Question(int _id, string _content, array<string, 4> _options, char _correct, string _explanation) {
    this->id = _id;
    this->content = _content;
    this->options = _options;
    this->correctAnswer = toupper(_correct);
    this->explanation = _explanation;
}
int Question::getId() const { return this->id; }
void Question::setId(int _id) { this->id = _id; }
string Question::getContent() const { return this->content; }
void Question::setContent(string _content) { this->content = _content; }
array<string, 4> Question::getOptions() const { return this->options; }
void Question::setOptions(array<string, 4> _options) { this->options = _options; }
char Question::getCorrectAnswer() const { return this->correctAnswer; }
void Question::setCorrectAnswer(char _correct) { this->correctAnswer = toupper(_correct); }
string Question::getExplanation() const { return this->explanation; }
void Question::setExplanation(string _explanation) { this->explanation = _explanation; }
bool Question::isValid() const {
    if (this->id <= 0) {
        return false;
    }
    if (this->content.empty()) {
        return false;
    }
    for (int i = 0; i < 4; i++) {
        if (this->options[i].empty()) {
            return false; 
        }
    }  
    if (this->correctAnswer != 'A' && this->correctAnswer != 'B' && 
        this->correctAnswer != 'C' && this->correctAnswer != 'D') {
        return false;
    }
    return true;
}
bool Question::checkAnswer(char userAnswer) const {
    char ans = toupper(userAnswer);
    if (ans == this->correctAnswer) {
        return true;
    }
    return false;
}
ostream& operator<<(ostream& out, const Question& q) {
    out << "Cau " << q.id << ": " << q.content << "\n";
    out << "A. " << q.options[0] << "\n";
    out << "B. " << q.options[1] << "\n";
    out << "C. " << q.options[2] << "\n";
    out << "D. " << q.options[3] << "\n";
    return out;
}