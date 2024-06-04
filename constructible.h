#ifndef CONSTRUCTIBLE_H
#define CONSTRUCTIBLE_H
#include "fraction.h"
#include <map>
#include <cmath>
#include <vector>
#include <ostream>
using std::map;
using std::pair;
using std::__gcd;
using std::make_pair;
using std::ostream;
using std::vector;





/*
    ------------------------ Constructible Numbers ------------------------

        This is a class for numbers that can be formed with an arbitrary*
    sequence of addition, subtraction, multiplication, division, and square
    roots. It defines the aforementioned operations (apart from division),
    an eval() method to evaluate a constructible number into a long double,
    and can print a constructible number as LaTeX code. The numbers are
    implementedas follows:

                a_0 + a_1 * sqrt(x_1) + a_2/ * sqrt(x_2) + ...

    Where a_n are rational numbers and x_n are constructible numbers.

    * My use case for the cos(2pi/65537) project didn't require division,
    and implementing it would require changing the entire structure of the
    class, so I chose to omit it.

    -----------------------------------------------------------------------
*/
class constructible
{
    public:
        constructible();
        constructible(fraction);
        constructible(fraction, const map<constructible, fraction>&);
        long double eval() const;
        constructible operator+(const constructible&) const;
        constructible operator-(const constructible&) const;
        constructible operator*(const constructible&) const;
        constructible operator*(const fraction&) const;
        constructible operator-() const;
        constructible operator+=(const constructible&);
        constructible operator-=(const constructible&);
        constructible operator*=(const constructible&);
        bool operator<(const constructible&) const;
        bool operator==(const constructible&) const;
        bool operator!=(const constructible&) const;
        bool operator>(const constructible&) const;
        bool operator>=(const constructible&) const;
        bool operator<=(const constructible&) const;
        friend const pair<constructible, fraction> radical(const constructible&, const constructible&);
        friend ostream& operator<<(ostream&, const constructible&);
        friend const constructible sqrt(const constructible&);
    private:
        fraction f;
        map<constructible, fraction> r;
        void cleanup();
};

#endif // CONSTRUCTIBLE_H
