#include <iostream>
#include <numeric>

class Fraction {
private:
    int numerator;
    int denominator;

    //Simplify function
    void simplify() {
        int gcd = std::gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
    }

public:
    Fraction(int num = 0, int denom = 1) : numerator(num), denominator(denom) {
        if (denominator == 0) {
            throw std::invalid_argument("Denominator cannot be zero");
        }
        simplify();
    }
    
    Fraction(const Fraction& other) : numerator(other.numerator), denominator(other.denominator) {}
    
    Fraction(Fraction&& other) noexcept : numerator(other.numerator), denominator(other.denominator) {
        other.numerator = 0;
        other.denominator = 1;
    }
    
    Fraction& operator = (const Fraction& other) {
        if (this != &other) {
            numerator = other.numerator;
            denominator = other.denominator;
        }
        return *this;
    }
    
    Fraction& operator=(Fraction&& other) noexcept {
        if (this != &other) {
            numerator = other.numerator;
            denominator = other.denominator;
            other.numerator = 0;
            other.denominator = 1;
        }
        return *this;
    }

    //Addition
    Fraction operator+(const Fraction& other) const {
        int num = numerator * other.denominator + other.numerator * denominator;
        int denom = denominator * other.denominator;
        return Fraction(num, denom);
    }

    // ubtraction
    Fraction operator-(const Fraction& other) const {
        int num = numerator * other.denominator - other.numerator * denominator;
        int denom = denominator * other.denominator;
        return Fraction(num, denom);
    }

    //Multiplication
    Fraction operator*(const Fraction& other) const {
        int num = numerator * other.numerator;
        int denom = denominator * other.denominator;
        return Fraction(num, denom);
    }

    //Division
    Fraction operator/(const Fraction& other) const {
        int num = numerator * other.denominator;
        int denom = denominator * other.numerator;
        if (denom == 0) {
            throw std::invalid_argument("Division by zero");
        }
        return Fraction(num, denom);
    }

    //Output
    friend std::ostream& operator<<(std::ostream& os, const Fraction& frac) {
        os << frac.numerator << '/' << frac.denominator;
        return os;
    }
};

int main() {
    Fraction frac1(3, 4);
    Fraction frac2(2, 5);

    std::cout << "Fraction 1: " << frac1 << "\n";
    std::cout << "Fraction 2: " << frac2 << "\n";
    std::cout << "Addition: " << frac1 + frac2 << "\n";
    std::cout << "Subtraction: " << frac1 - frac2 << "\n";
    std::cout << "Multiplication: " << frac1 * frac2 << "\n";
    std::cout << "Division: " << frac1 / frac2 << "\n";

    return 0;
}