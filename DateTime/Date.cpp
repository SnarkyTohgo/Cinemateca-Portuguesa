#include "Date.h"

/*
 * CONSTRUCTORS
 */

Date::Date(u_int d, u_int m, u_int a) {
    this->d = d;
    this->m = m;
    this->a = a;
}


/*
 * MEMBER FUNCTIONS
 */

u_int
Date::getD() const {
    return this->d;
}

u_int
Date::getM() const {
    return this->m;
}

u_int
Date::getA() const {
    return this->a;
}


/*
 * OPERATOR OVERLOADS
 */

ostream&
operator <<(ostream& out, const Date& date) {
    out << date.getD() << "/" << date.getM() << "/" << date.getA() << endl;
    return out;
}

bool
Date::operator ==(Date date) {
    return (this->d == date.getD() and this->m == date.getM() and this->a == date.getA());
}

bool
Date::operator <(Date date) {
    if (this->a == date.getA()){
        if (this->m == date.getM()){
            return this->d < date.getD();
        } else
            return this->m < date.getM();
    } else
        return this->a < date.getA();
}
