#ifndef COMPLEXNUMBERS_COMPLEXNUMBERS_H
#define COMPLEXNUMBERS_COMPLEXNUMBERS_H

class ComplexNumber
{
private:
    double ReZ{};
    double ImZ{};

public:
    ComplexNumber( double ReZ_, double ImZ_ ) noexcept;

    ComplexNumber add( const ComplexNumber& other ) noexcept;
    ComplexNumber subtract( const ComplexNumber& other ) noexcept;
    ComplexNumber multiply( const ComplexNumber& other ) noexcept;
    double abs( ) const noexcept ;

    ~ComplexNumber();
};

#endif
