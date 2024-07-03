// 214984932 oriyas.07@gmail.com

// These class was copied from the curse github, I will add documentation to what I added.
#include <iostream>
#include <ostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <sstream>

class Complex
{
    double _re, _im;

public:
    Complex() { _re = _im = 0; } // inline constructor
    Complex(double r, double i) : _re(r), _im(i) {}

    // setters
    Complex &setReal(double r);
    Complex &setImage(double i);

    // getters
    double getImage() const;
    double getReal() const;

    /**
     * This function creates a string from the complex data.
     * @returns a string in the format: _re+_imi.
     */
    std::string to_string() const;

    /**
     * This function checks if one Complex is bigger than the other.
     * @param x1 - the first Complex to compare.
     * @param x2 - the second Complex to compare.
     * @returns true if x1 is bigger than x2, false otherwise.
     */
    friend bool operator>(const Complex &x1, const Complex &x2);

    /**
     * This function is overload for the operator <<.
     * @param output - ostream to return.
     * @param c - Complex to print.
     * @returns - ostream.
     */
    friend std::ostream &operator<<(std::ostream &output, const Complex &c);
};
