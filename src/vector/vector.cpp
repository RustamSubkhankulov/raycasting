#include <math.h>

//=========================================================

#include "../../include/vector/vector.hpp" 

//=========================================================

// Works only for 2d
Vector orthogonal_2d_only(const Vector& v)
{
    return Vector {v.y_, -v.x_};
}

//---------------------------------------------------------

Vector operator+ (const Vector& a, const Vector& b)
{
    Vector res = a;
    res += b;
    return res;
}

Vector operator- (const Vector& a, const Vector& b)
{
    Vector res = a;
    res -= b;
    return res;
}

Vector operator* (const Vector& v, double mul)
{
    return Vector {v.x_ * mul, v.y_ * mul, v.z_ * mul};
}

Vector operator* (double mul, const Vector& v)
{
    return Vector {v.x_ * mul, v.y_ * mul, v.z_ * mul};
}

double operator* (const Vector& a, const Vector& b)
{
    return a.x_ * b.x_ + a.y_ * b.y_ + a.z_ * b.z_;
}

Vector operator% (const Vector& a, const Vector& b)
{
    return Vector {a.x_ * b.x_, a.y_ * b.y_, a.z_ * b.z_};
}

//---------------------------------------------------------

void Vector::rotate_2d_only(double rad_angle)
{
    double sinus  = sin(rad_angle);
    double cosine = cos(rad_angle);

    rotate_2d_only(sinus, cosine);
}

void Vector::rotate_2d_only(double sin, double cos)
{
    double x1 = x_;
    double y1 = y_;

    set(cos * x1 - sin * y1, 
        sin * x1 + cos * y1);
}

//---------------------------------------------------------

void Vector::normalize()
{
    double length = len();
    (*this) *= (1 / length);
}

//---------------------------------------------------------