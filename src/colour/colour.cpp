
//=========================================================

#include "../../include/colour/colour.hpp"

//=========================================================

inline void Colour::set_r(const unsigned r)
{
    unsigned r_ = r;

    if (r > 255)
        r_ = 255;
    else if (r < 0)
        r_ = 0;

    rgb_v_.set_x(double(r_));
}

//---------------------------------------------------------

inline void Colour::set_g(const unsigned g)
{
    unsigned g_ = g;

    if (g > 255)
        g_ = 255;
    else if (g < 0)
        g_ = 0;

    rgb_v_.set_y(double(g_));
}

//---------------------------------------------------------

inline void Colour::set_b(const unsigned b)
{
    unsigned b_ = b;

    if (b > 255)
        b_ = 255;
    else if (b < 0)
        b_ = 0;

    rgb_v_.set_z(double(b_));
}

//---------------------------------------------------------

void Colour::rgb_norm()
{
    double r = rgb_v_.x();
    double g = rgb_v_.y();
    double b = rgb_v_.z();

    if (r > 255) r = 255;
    if (r < 0)   r = 0;

    if (g > 255) g = 255;
    if (g < 0)   g = 0;

    if (b > 255) b = 255;
    if (b < 0)   b = 0;

    rgb_v_.set(r, g, b);
}

//---------------------------------------------------------

Colour operator- (const Colour& c)
{
    return Colour{ - c.rgb_v_ };
}

Colour operator+ (const Colour& a, const Colour& b)
{
    return Colour{a.rgb_v_ + b.rgb_v_};
}

Colour operator- (const Colour& a, const Colour& b)
{
    return Colour{a.rgb_v_ - b.rgb_v_};
}

Colour operator% (const Colour& a, const Colour& b)
{
    Colour c = a;
    c %= b;

    return c;
}

Colour operator* (const Colour& c, const double m)
{
    return Colour{c.rgb_v_ * m};
}

Colour operator* (const double m, const Colour& c)
{
    return Colour{m * c.rgb_v_};
}
