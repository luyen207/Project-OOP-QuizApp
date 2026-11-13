#pragma once
#include <iostream>
#include <string>
using namespace std;
class Person {
protected: 
    string hoten;
    string maso;
public:
    Person(string ten = "", string ma = "") {
        this->hoten = ten;
        this->maso = ma;
    }

    // Các hàm Getter / Setter (Chương 2)
    string getHoTen() const { return this->hoten; }
    void setHoTen(string ten) { this->hoten = ten; }

    string getMaSo() const { return this->maso; }
    void setMaSo(string ma) { this->maso = ma; }
    friend ostream& operator<<(ostream& out, const Person& p);
};