#include <iostream>
#include "ComplexNumbers.h"

auto calculateSumOfAbsoluteSquares(const ComplexNumber* numbers, int N) noexcept -> double {
    auto sum = 0.0f;
    for (auto i = 0; i < N; ++i) {
        sum += ( numbers[i].abs() * numbers[i].abs() );
    }
    return sum;
}

int main() {
    constexpr const int N = 3;
    ComplexNumber numbers[N] = {
            { 1.0, 2.0 },
            { -3.0, 4.0 },
            { 5.0, -6.0 }
    };

    double result = calculateSumOfAbsoluteSquares( numbers, N );

    std::cout << "Absolute sum is -> : " << result << std::endl;

    return 0;
}
