#pragma once

//=========================================================

#include "../vector/vector.hpp"

//=========================================================

class Colour  
{
    Vector rgb_v_ = {};

    public: 

        Colour() {}

        Colour(unsigned r, unsigned g, unsigned b):
            rgb_v_(r, g, b)
            {
                rgb_norm();
            }

        Colour(const Vector& v):
            rgb_v_(v)
            {
                rgb_norm();
            }

        ~Colour()            = default;
        Colour(const Colour&) = default;
        Colour(Colour&&)      = default;

        Colour& operator= (const Colour&) = default;
        Colour& operator= (Colour&&)      = default;

        void set(const unsigned r,
                 const unsigned g,
                 const unsigned b)
            {
                rgb_v_.set(r, g, b);
                rgb_norm();
            }

        inline void set_r(const unsigned r);
        inline void set_g(const unsigned g);
        inline void set_b(const unsigned b);

        unsigned char get_r() const 
            {
                return (unsigned char)rgb_v_.x();
            };

        unsigned char get_g() const
            {
                return (unsigned char)rgb_v_.y();
            };

        unsigned char get_b() const 
            {
                return (unsigned char)rgb_v_.z();
            };

        Colour& operator*= (const double mul)
            {
                rgb_v_ *= mul;
                rgb_norm();
                return *this;
            }

        Colour& operator+= (const Colour& c)
            {
                rgb_v_ += c.rgb_v_;
                rgb_norm();
                return *this;
            }

        Colour& operator-= (const Colour& c)
            {
                rgb_v_ -= c.rgb_v_;
                rgb_norm();
                return *this;
            }

        Colour& operator%= (const Colour& c)
            {
                double r = rgb_v_.x() * c.rgb_v_.x();
                double g = rgb_v_.y() * c.rgb_v_.y();
                double b = rgb_v_.z() * c.rgb_v_.z();

                rgb_v_.set(r, g, b);
                return *this;
            }

        friend Colour operator- (const Colour& c);
        friend Colour operator+ (const Colour& a, const Colour& b);
        friend Colour operator- (const Colour& a, const Colour& b);
        friend Colour operator% (const Colour& a, const Colour& b);
        friend Colour operator* (const Colour& c, const double m);
        friend Colour operator* (const double m, const Colour& c);

    private:

        void rgb_norm();
};
