#include "Person.h"
ostream& operator<<(ostream& out, const Person& p) {
    out << "Ho ten: " << p.hoten << " | Ma so: " << p.maso;
    return out;
}