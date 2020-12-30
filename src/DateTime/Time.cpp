#include "Time.h"


/*
 * CONSTRUCTORS
 */

Time::Time(int h, int m, int s) {
    this->h = h;
    this->m = m;
    this->s = s;

    if (h > 24)
        throw InvalidTime();

    if (m > 59)
        throw InvalidTime();

    if (s > 59)
        throw InvalidTime();
}


/*
 * MEMBER FUNCTIONS
 */

// GETTERS
int
Time::getH() const {
    return this->h;
}

int
Time::getM() const {
    return this->m;
}

int
Time::getS() const {
    return this->s;
}

// SETTERS

void
Time::setH(int h){
    this->h = h;
}

void
Time::setM(int m){
    this->m = m;
}

void
Time::setS(int s){
    this->s = s;
}


/*
 * OPERATOR OVERLOADS
 */

ostream&
operator <<(ostream& out, const Time& time) {
    out << time.getH() << ":" << time.getM() << ":" << time.getS() << endl;
    return out;
}

bool
Time::operator ==(Time t) {
    return (this->h == t.getH() and this->m == t.getM() and this->s == t.getS());
}

bool
Time::operator <(Time t) {
    if (this->h == t.getH()){
        if (this->m == t.getM()){
            return this->s < t.getS();
        } else
            return this->m < t.getM();
    } else
        return this->h < t.getH();
}

bool
Time::operator >(Time t) {
    if (this->h == t.getH()){
        if (this->m == t.getM()){
            return this->s > t.getS();
        } else
            return this->m > t.getM();
    } else
        return this->h > t.getH();
}
