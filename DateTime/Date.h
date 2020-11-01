#ifndef CINEMATECAPORTUGUESA_DATE_H
#define CINEMATECAPORTUGUESA_DATE_H

#include "../Utils/utils.h"

class Date {
private:
    u_int d, m, a;

public:
    Date(){}
    Date(u_int d, u_int m, u_int a);

    u_int getD() const;
    u_int getM() const;
    u_int getA() const;

    bool operator ==(const Date date);
    bool operator <(const Date date);           // d1 ocorreu antes que d2

    friend ostream& operator <<(ostream& out, const Date& date);
};


#endif //CINEMATECAPORTUGUESA_DATE_H
