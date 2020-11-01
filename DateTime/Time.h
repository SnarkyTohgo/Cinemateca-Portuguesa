#ifndef CINEMATECAPORTUGUESA_TIME_H
#define CINEMATECAPORTUGUESA_TIME_H

#include "../Utils/utils.h"


class Time {
private:
    int h, m, s;

public:
    Time(){};
    Time(int h, int m, int s);

    int getH() const;
    int getM() const;
    int getS() const;

    void setH(int h);
    void setM(int m);
    void setS(int s);


    bool operator ==(const Time t);
    bool operator <(const Time t);
    bool operator >(const Time t);

    friend ostream& operator <<(ostream& out, const Time& time);
};


#endif //CINEMATECAPORTUGUESA_TIME_H
