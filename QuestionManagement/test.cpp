#include <iostream>
#include "Question.h"
#include "Person.h"
using namespace std;
int main() {
    cout << "=== KIEM THU MODULE QUESTION (TV2) ===" << endl;
    array<string, 4> dapan1 = {"Tinh dong goi", "Tinh ke thua", "Tinh da hinh", "Tinh truu tuong"};
    Question q1(1, "Tinh chat nao che giau du lieu ben trong doi tuong?", dapan1, 'A', "Dong goi giup che giau du lieu.");

    cout << "\n[Test 1] Kiem tra cau hoi hop le:" << endl;
    if (q1.isValid() == true) {
        cout << "-> Ket qua: HOP LE" << endl;
        cout << q1; 
    } else {
        cout << "-> Ket qua: KHONG HOP LE" << endl;
    }
    cout << "\n[Test 2] Kiem tra cau hoi bi loi (thieu dap an):" << endl;
    array<string, 4> dapAn2 = {"class", "struct", "", "union"}; 
    Question q2(2, "Tu khoa nao dung de khai bao lop trong C++?", dapAn2, 'A', "");
    if (q2.isValid() == false) {
        cout << "-> Ket qua: Da phat hien loi (KHONG HOP LE)" << endl;
    } else {
        cout << "-> Ket qua: Loi khong phat hien duoc" << endl;
    }
    cout << "\n[Test 3] Kiem tra ham checkAnswer:" << endl;
    cout << "Dap an dung cua cau 1 la: A (Tinh dong goi)" << endl;
    if (q1.checkAnswer('A') == true) {
        cout << "Nguoi dung chon 'A' -> DUNG" << endl;
    }
    if (q1.checkAnswer('a') == true) {
        cout << "Nguoi dung chon 'a' -> DUNG (da tu dong viet hoa)" << endl;
    }
    if (q1.checkAnswer('C') == false) {
        cout << "Nguoi dung chon 'C' -> SAI" << endl;
    }
    cout << "\n[Test 4] Kiem tra lop Person (Nguoi dung):" << endl;
    Person p1("Nguyen Van Lap Trinh", "SV_IT001");
    cout << p1 << endl; 
    return 0;
}