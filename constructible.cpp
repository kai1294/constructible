#include "constructible.h"

// boilerplate code starts here
const constructible one(fraction(1, 1));
constructible::constructible()
{
    this->f = fraction(0, 1);
}constructible::constructible(fraction f)
{
    this->f = f;
}
bool constructible::operator==(const constructible &other) const
{
    return this->eval() == other.eval(); // could have floating point nastiness maybe
}
bool constructible::operator!=(const constructible &other) const
{
    return this->eval() != other.eval();
}
bool constructible::operator<(const constructible &other) const
{
    return this->eval() < other.eval();
}
bool constructible::operator<=(const constructible &other) const
{
    return this->eval() <= other.eval();
}
bool constructible::operator>(const constructible &other) const
{
    return this->eval() > other.eval();
}
bool constructible::operator>=(const constructible &other) const
{
    return this->eval() >= other.eval();
}
constructible constructible::operator+=(const constructible& other)
{
    *this = *this + other;
    this->cleanup();
    return *this;
}
constructible constructible::operator-=(const constructible& other)
{
    *this = *this - other;
    this->cleanup();
    return *this;
}
constructible constructible::operator*=(const constructible& other)
{
    *this = *this * other;
    this->cleanup();    return *this;
}
constructible constructible::operator*(const constructible& other) const
{
    constructible res;
    for(auto i: this->r)
    {
        res.r[i.first] = i.second * other.f;
    }
    for(auto i: other.r)
    {
        res.r[i.first] += i.second * this->f;
    }
    for(auto i: this->r)
    {
        for(auto j: other.r)
        {
            pair<constructible, fraction> p = radical(i.first, j.first);
            if(p.first != one)res.r[p.first] += p.second * i.second * j.second;
            else res.f += p.second * i.second * j.second;
        }
    }
    res.f +=  this->f * other.f;
    res.cleanup();
    return res;
}
constructible constructible::operator+(const constructible& other) const
{
    constructible res = *this;
    res.f += other.f;
    for(auto i: other.r)
    {
        res.r[i.first] += i.second;
    }
    res.cleanup();
    return res;
}
constructible constructible::operator-(const constructible& other) const
{
    constructible res = *this;
    res.f -= other.f;
    for(auto i: other.r)
    {
        res.r[i.first] -= i.second;
    }
    res.cleanup();
    return res;
}
constructible constructible::operator-() const
{
    constructible res = *this;
    res.f =- res.f;
    for(auto i: res.r)
    {
        res.r[i.first] = -i.second;
    }
    res.cleanup();    return res;
}
const constructible sqrt(const constructible& a)
{
    constructible res;
    pair<constructible, fraction> p = radical(a, one);
    p.first.cleanup();
    if(p.first != one)res.r[p.first] = p.second;
    else res.f = p.second;
    res.cleanup();
    return res;
}
constructible constructible::operator*(const fraction &f) const
{
    constructible res = *this;
    res.f *= f;
    for(auto i: res.r)
    {
        res.r[i.first] *= f;
    }
    res.cleanup();
    return res;
}
ostream& operator<<(ostream& os, const constructible& c)
{
    // Prints the number as LaTeX to os
    os << (c.f);
    for(auto i: c.r)
    {
        if(i.second.a>=0)os<< '+';
        os << i.second << "\\sqrt{" << i.first << "}";
    }
    return os;
}
// end of boilerplate
const pair<constructible, fraction> radical(const constructible &a, const constructible &b)
{
    // takes sqrt(a * b) and simplifies it
    // idk why this isn't just sqrt()
    // don't worry about it imo
    constructible res = a * b;
    res.cleanup();
    fraction g = res.f;
    for(auto i: res.r)
    {
        g = gcd(g, i.second);
    }
    fraction f(1, 1);
    for(int i = 2; i * i <= g.a; i++)
    {
        while(g.a % (i * i) == 0)
        {
            g.a /= (i * i);
            f.a *= i;
        }
    }
    for(int i = 2; i * i <= g.b; i++)
    {
        while(g.b % (i * i) == 0)
        {
            g.b /= (i * i);
            f.b *= i;
        }
    }
    res.f /= f * f;
    for(auto i: res.r)
    {
        res.r[i.first] /= f * f;
    }
    res.cleanup();
    return make_pair(res, f);
}
void constructible::cleanup()
{
    // cleanup function to keep the format of the number consistent.
    // called frequently in functions that modify its internal structure
    // perhaps a bit too frequently oops
    vector<constructible> v;
    this->f += this->r[one];
    this->r.erase(one);
    for(auto i: this->r)
    {
        if(i.second.a == 0)v.push_back(i.first);
        // if i modify this->r here i would invalidate the iterators
    }
    for(constructible i: v)
    {
        this->r.erase(i);
        // so i modify it here
    }
}
long double constructible::eval() const
{
    // evaluate
    long double res = this->f.eval();
    for(auto i: this->r)
    {
        res += sqrt(i.first.eval())*i.second.eval();
    }
    return res;
}
