#include <iostream>
#include <cmath>

class Complex
{
private:
    double *r;
    double *i;

public:
    Complex();
    Complex(double real, double imag);
    Complex(const Complex &obj);
    Complex(Complex &&obj);
    ~Complex();

    Complex operator+(const Complex &obj);
    Complex operator-(const Complex &obj);
    Complex operator*(const Complex &obj);
    Complex operator/(const Complex &obj);
    Complex &operator=(const Complex &obj);
    Complex &operator=(Complex &&obj);
    bool operator==(Complex const &obj);
    bool operator!=(Complex const &obj);
    Complex conj();
    double real() const;
    double imag() const;
    double abs() const;
    double phi() const;
    Complex csqrt();
    Complex cexp();
    Complex clog();
    Complex cpow(double t);
    friend std::ostream &operator<<(std::ostream &out, const Complex &z);
};