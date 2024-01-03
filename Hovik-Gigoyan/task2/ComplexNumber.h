#ifndef COMPLEXNUMBER_H
#define COMPLEXNUMBER_H

class ComplexNumber {
public:
    ComplexNumber(double real = 0.0, double imaginary = 0.0);
    ComplexNumber Add(const ComplexNumber& other) const;
    ComplexNumber Subtract(const ComplexNumber& other) const;
    ComplexNumber Multiply(const ComplexNumber& other) const;
    double Abs() const;

private:
    double real;
    double imaginary;
};

#endif
