#include "complex.hpp"

template <typename T>
int sgn(T val)
{
    return (T(0) < val) - (val < T(0));
}

Complex::Complex()
{
    r = new double(0);
    i = new double(0);
}

Complex::Complex(double real, double imag)
{
    r = new double(real);
    i = new double(imag);
}

Complex::Complex(const Complex &obj)
{
    r = new double(*obj.r);
    i = new double(*obj.i);
}

Complex::Complex(Complex &&obj)
{
    r = obj.r;
    obj.r = nullptr;
    i = obj.i;
    obj.i = nullptr;
}

std::ostream &operator<<(std::ostream &out, const Complex &z)
{
    if (z.imag() > 0)
    {
        out << z.real() << " + " << z.imag() << "i";
    }
    else
    {
        out << z.real() << " - " << -z.imag() << "i";
    }
    return out;
}

Complex Complex::operator+(const Complex &obj)
{
    Complex res;
    *res.r = *r + *obj.r;
    *res.i = *i + *obj.i;
    return res;
}

Complex Complex::operator-(const Complex &obj)
{
    Complex res;
    *res.r = *r - *obj.r;
    *res.i = *i - *obj.i;
    return res;
}

Complex Complex::operator*(const Complex &obj)
{
    Complex res;
    *res.r = *r * (*obj.r) - *i * (*obj.i);
    *res.i = *r * (*obj.i) + *i * (*obj.r);
    return res;
}

Complex Complex::operator/(const Complex &obj)
{
    Complex res;
    double den = (*obj.r) * (*obj.r) + (*obj.i) * (*obj.i);
    *res.r = (*r * (*obj.r) + *i * (*obj.i)) / den;
    *res.i = (*i * (*obj.r) - *r * (*obj.i)) / den;
    return res;
}

Complex &Complex::operator=(const Complex &obj)
{
    if (this != &obj)
    {
        delete r;
        r = new double(*obj.r);
        delete i;
        i = new double(*obj.i);
    }
    return *this;
}

Complex &Complex::operator=(Complex &&obj)
{
    if (this != &obj)
    {
        delete r;
        r = obj.r;
        obj.r = nullptr;
        delete i;
        i = obj.i;
        obj.i = nullptr;
    }
    return *this;
}

bool Complex::operator==(const Complex &obj)
{
    if ((*r == *obj.r) && (*i == *obj.i))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Complex::operator!=(const Complex &obj)
{
    if ((*r != *obj.r) || (*i != *obj.i))
    {
        return true;
    }
    else
    {
        return false;
    }
}

Complex Complex::conj()
{
    Complex res;
    *res.r = *r;
    *res.i = -*i;
    return res;
}

double Complex::real() const
{
    return *r;
}

double Complex::imag() const
{
    return *i;
}

double Complex::abs() const
{
    return sqrt((*r) * (*r) + (*i) * (*i));
}

double Complex::phi() const
{
    if ((*i != 0) || (*r > 0))
    {
        return 2 * atan(*i / (this->abs() + *r));
    }
    else if ((*r < 0) && (*i == 0))
    {
        return M_PI;
    }
    else
    {
        return INFINITY;
    }
}

Complex Complex::csqrt()
{
    Complex result;
    *result.r = sqrt((*r + this->abs()) / 2);
    *result.i = sgn(*i) * sqrt((-*r + this->abs()) / 2);
    return result;
}

Complex Complex::cexp()
{
    Complex result;
    *result.r = exp(*r) * cos(*i);
    *result.i = exp(*r) * sin(*i);
    return result;
}

Complex Complex::clog()
{
    Complex result;
    *result.r = log(this->abs());
    *result.i = atan2(*i, *r);
    return result;
}

Complex Complex::cpow(double t)
{
    Complex result;
    double arg = exp(t * log(this->abs()));
    double phi = this->phi();
    *result.r = arg * (cos(phi * t));
    *result.i = arg * (sin(phi * t));
    return result;
}

Complex::~Complex()
{
    delete r;
    delete i;
}