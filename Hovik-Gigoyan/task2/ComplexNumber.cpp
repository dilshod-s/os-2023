#include "ComplexNumber.h"
#include <cmath>

ComplexNumber::ComplexNumber(double r, double i) : real(r), imaginary(i) {}

ComplexNumber ComplexNumber::Add(const ComplexNumber& other) const {
    return ComplexNumber(real + other.real, imaginary + other.imaginary);
}

ComplexNumber ComplexNumber::Subtract(const ComplexNumber& other) const {
    return ComplexNumber(real - other.real, imaginary - other.imaginary);
}

ComplexNumber ComplexNumber::Multiply(const ComplexNumber& other) const {
    return ComplexNumber(real * other.real - imaginary * other.imaginary,
                         real * other.imaginary + imaginary * other.real);
}

double ComplexNumber::Abs() const {
    return std::sqrt(real * real + imaginary * imaginary);
}
