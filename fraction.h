#ifndef FRACTION_H
#define FRACTION_H
#include <algorithm>
#include <ostream>
//#include "constructible.h"
using std::ostream;
using std::__gcd;


// i spent all my energy making a fancy header for constructible.h
// so uh fracton ig
// highest ratio of boilerplate to substance ratio ever seen
class fraction
{
    public:
        fraction();
        fraction(int, int);
        fraction operator+(const fraction&) const;
        fraction operator-(const fraction&) const;
        fraction operator*(const fraction&) const;
        fraction operator/(const fraction&) const;
        fraction operator-() const;
        fraction operator+=(const fraction&);
        fraction operator-=(const fraction&);
        fraction operator*=(const fraction&);
        fraction operator/=(const fraction&);
        bool operator<(const fraction&) const;
        bool operator<=(const fraction&) const;
        bool operator>(const fraction&) const;
        bool operator>=(const fraction&) const;
        bool operator==(const fraction&) const;
        bool operator!=(const fraction&) const;
        int a, b;
        long double eval() const;
    private:
        void simplify();
};
ostream& operator<<(ostream&, const fraction&);
const fraction gcd(const fraction, const fraction);
#endif // FRACTION_H
