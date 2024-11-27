#include <iostream>

class Complex {
public:
    double real;
    double imag;

    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    Complex(const Complex& other) : real(other.real), imag(other.imag) {}

    Complex(Complex&& other) noexcept : real(other.real), imag(other.imag) {
        other.real = 0;
        other.imag = 0;
    }

    Complex& operator=(const Complex& other) {
        if (this == &other) return *this;
        real = other.real;
        imag = other.imag;
        return *this;
    }

    Complex& operator=(Complex&& other) noexcept {
        if (this == &other) return *this;
        real = other.real;
        imag = other.imag;
        other.real = 0;
        other.imag = 0;
        return *this;
    }

    //Addition
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    //Subtraction
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    // Multiplication operator
    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
    }

    //Division
    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imag * other.imag;
        return Complex((real * other.real + imag * other.imag) / denominator,
                       (imag * other.real - real * other.imag) / denominator);
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real << " + " << c.imag << "i";
        return os;
    }
};

int main() {
    Complex complex1(4, 5);
    Complex complex2 (2, 3);

    std::cout << "Complex no. 1: " << complex1 << std::endl;
    std::cout << "Complex no. 2 : " << complex2  << std::endl;
    std::cout << "Addition: " << complex1 + complex2  << std::endl;
    std::cout << "Subtraction: " << complex1 - complex2  << std::endl;
    std::cout << "Multiplication: " << complex1 * complex2 << std::endl;
    std::cout << "Division: " << complex1 / complex2 << std::endl;

    return 0;
}