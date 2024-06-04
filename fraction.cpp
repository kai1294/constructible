#include "fraction.h"

fraction::fraction()
{
    this->a = 0;
    this->b = 1;
}
fraction::fraction(int a, int b = 1)
{
    this->a = a;
    this->b = b;
    this->simplify();
}
void fraction::simplify()
{
    int g = __gcd(this->a, this->b);
    this->a /= g;
    this->b /= g;
    if(b<0)
    {
        a = -a;
        b = -b;
    }
}
fraction fraction::operator+(const fraction& other) const
{
    int a = this->a * other.b + this->b * other.a;
    int b = this->b * other.b;
    fraction res(a, b);
    return res;
}
fraction fraction::operator-(const fraction& other) const
{
    int a = this->a * other.b - this->b * other.a;
    int b = this->b * other.b;
    fraction res(a, b);
    return res;

}
fraction fraction::operator-() const
{
    fraction res(-this->a, b);
    return res;

}
fraction fraction::operator*(const fraction& other) const
{
    int a = this->a * other.a;
    int b = this->b * other.b;
    fraction res(a, b);
    return res;
}
fraction fraction::operator/(const fraction& other) const
{
    int a = this->a * other.b;
    int b = this->b * other.a;
    fraction res(a, b);
    return res;
}
bool fraction::operator<(const fraction& other) const
{
    if(this->a < other.a)
    {
        return true;
    }
    if(this->a > other.a)
    {
        return false;
    }

    return this->b < other.b;
}
bool fraction::operator==(const fraction& other) const
{
    return this->a==other.a&&this->b==other.b;
}
bool fraction::operator<=(const fraction& other) const
{
    return *this<other||*this==other;
}
bool fraction::operator>(const fraction& other) const
{
    return !(*this<other||*this==other);
}
bool fraction::operator>=(const fraction& other) const
{
    return !(*this<other);
}
bool fraction::operator!=(const fraction& other) const
{
    return !(*this==other);
}
fraction fraction::operator+=(const fraction& other)
{
    *this = *this + other;
    return *this;
}
fraction fraction::operator-=(const fraction& other)
{
    *this = *this - other;
    return *this;
}
fraction fraction::operator*=(const fraction& other)
{
    *this = *this * other;
    return *this;
}
fraction fraction::operator/=(const fraction& other)
{
    *this = *this / other;
    return *this;
}
ostream& operator<<(ostream& os, const fraction& c)
{
    // latex
    if(c.b == 1)
    {
        os << c.a;
        return os;
    }
    if(c.a<0)
    {
        os << "-\\frac{" << -c.a << "}{" << c.b << "}";
    }
    else
    {
        os << "\\frac{" << c.a << "}{" << c.b << "}";
    }
    return os;
}
const fraction gcd(const fraction a, const fraction b)
{
    if(a.a==0)return b;
    if(b.a==0)return a;
    int ga = __gcd(a.a, b.a);
    int gb = __gcd(a.b, b.b);
    return fraction(ga, gb);
}

long double fraction::eval() const
{
    return ((long double)a)/((long double)b);
}
