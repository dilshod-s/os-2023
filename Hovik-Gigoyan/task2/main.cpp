#include <iostream>
#include "ComplexNumber.h"

double SumOfSquaresAbs(const ComplexNumber* numbers, int length) {
    double sum = 0.0;
    for (int i = 0; i < length; ++i) {
        ComplexNumber squared = numbers[i].Multiply(numbers[i]);
        sum += squared.Abs();
    }
    return sum;
}

int main() {
    ComplexNumber numbers[] = {
        ComplexNumber(1, 2),
        ComplexNumber(3, 4),
        ComplexNumber(5, 6)
    };

    double result = SumOfSquaresAbs(numbers, 3);
    std::cout << "Result: " << result << std::endl;
    return 0;
}
