#include "ComplexNumbers.h"
#include <cmath>

ComplexNumber::ComplexNumber(double ReZ_, double ImZ_) noexcept : ReZ{ ReZ_ }, ImZ{ ImZ_ } {}

ComplexNumber ComplexNumber::add(const ComplexNumber &other) noexcept {
    return { this->ReZ + other.ReZ, this->ImZ + other.ImZ };
}

ComplexNumber ComplexNumber::subtract(const ComplexNumber &other) noexcept {
    return { this->ReZ - other.ReZ, this->ImZ - other.ImZ };
}

ComplexNumber ComplexNumber::multiply(const ComplexNumber &other) noexcept {
    return {
        this->ReZ * other.ReZ - this->ImZ * other.ImZ,
        this->ImZ * other.ImZ + this->ImZ * other.ReZ
    };
}

double ComplexNumber::abs() const noexcept {
    return std::sqrt( this->ReZ * this->ReZ + this->ImZ * this->ImZ );
}

ComplexNumber::~ComplexNumber() = default;

