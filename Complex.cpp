// 214984932 oriyas.07@gmail.com
#include "Complex.hpp"

Complex &Complex::setReal(double r)
{
    this->_re = r;
    return *this;
}

Complex &Complex::setImage(double i)
{
    this->_im = i;
    return *this;
}

double Complex::getImage() const
{
    return this->_im;
}

double Complex::getReal() const
{
    return this->_re;
}

std::string Complex::to_string() const
{
    return std::to_string((int)_re) + '+' + std::to_string((int)_im) + 'i';
}
bool operator>(const Complex &x1, const Complex &x2)
{
    // compare by the real part first and than by the image part
    if (x1.getReal() > x2.getReal() || (x1.getReal() == x2.getReal() && x1.getImage() > x2.getImage()))
    {
        return true;
    }
    return false;
}

std::ostream &operator<<(std::ostream &output, const Complex &c)
{
    return (output << c.getReal() << '+' << c.getImage() << 'i');
}
