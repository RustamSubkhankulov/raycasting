#pragma once 

//=========================================================

#include <math.h>

class Vector;

class Vector_posed;

//=========================================================

class Vector
{
    double x_ = 0, y_ = 0, z_ = 0;
    double len_ = NAN;

    public:

        Vector() {}

        Vector(double x, double y, double z = 0):
            x_(x), 
            y_(y),
            len_( ((!x_) && (!y_) && (!z_))? 0: NAN )
            {}

        Vector(const Vector&) = default; //copy ctor
        Vector(Vector&&)      = default; //move ctor

        Vector& operator= (const Vector&)  = default; //copy assignment
        Vector& operator= (Vector&&)       = default; //move assignment

        void set(double x, double y, double z = 0)
            {
                len_ = ((fabs(x_) == fabs(x)) 
                     && (fabs(y_) == fabs(y))
                     && (fabs(z_) == fabs(z)))? len_: NAN;
                x_ = x; 
                y_ = y;
                z_ = z;
            }

        Vector& operator*= (double mul)
            {
                set(x_ * mul, y_ * mul, z_ * mul);
                return *this;
            }

        Vector& operator+= (const Vector& v)
            {
                set(x_ + v.x_, y_ + v.y_, z_ + v.z_);
                return *this;
            }

        Vector& operator-= (const Vector& v)
            {
                set(x_ - v.x_, y_ - v.y_, z_ - v.z_);
                return *this;
            }
        
        Vector operator- ()
            {
                return Vector {- x_, - y_, -z_};
            }

        double x() const { return x_; }
        double y() const { return y_; }
        double z() const { return z_; }

        double len()
            {
                if (!isnan(len_))
                    return len_;

                len_ = sqrt(pow(x_,2) + pow(y_,2) + pow(z_,2));
                return len_;
            }

        void rotate_2d_only(double rad_angle);
        void rotate_2d_only(double sin, double cos);

        void normalize();

        friend Vector orthogonal_2d_only(const Vector& v);

        friend Vector operator+ (const Vector& a, const Vector& b);   
        friend Vector operator- (const Vector& a, const Vector& b);  
        friend double operator* (const Vector& a, const Vector& b);  
        friend Vector operator% (const Vector& a, const Vector& b);
        friend Vector operator* (const Vector& v, double mul);
};

//---------------------------------------------------------

class Vector_posed 
{
    Vector point_;
    Vector vector_;

    public:

        Vector_posed():
            point_(),
            vector_()
            {}
        
        Vector_posed(const Vector& r, const Vector& v):
            point_ (r),
            vector_(v)
            {}

        Vector_posed(const Vector_posed&) = default;
        Vector_posed(Vector_posed&&)      = default;

        Vector_posed& operator= (const Vector_posed&)  = default; //copy assignment
        Vector_posed& operator= (Vector_posed&&)       = default; //move assignment

        void set_point(const Vector& r)
            {
                point_ = r;
            }

        void set_vector(const Vector& v)
            {
                vector_ = v;
            }

        void rotate_2d_only(double rad_angle)
            {
                vector_.rotate_2d_only(rad_angle);
            }

        void rotate_2d_only(double sin, double cos)
            {
                vector_.rotate_2d_only(sin, cos);
            }

        Vector vector() const { return vector_; }
        Vector point()  const { return point_;  }

        Vector_posed& operator*= (double mul)
            {
                vector_ *= mul;
                return *this;
            }
        
        Vector_posed& operator+= (const Vector& v)
            {
                vector_ += v;
                return *this;
            }
        
        Vector_posed operator-()
            {
                return Vector_posed {point_, - vector_};
            }

        double len()
            {
                return vector_.len();
            }

        void normalize()
            {
                vector_.normalize();
            }

        void set_dir(const Vector& dir)
            {
                set_vector( dir - point_ );
            }
};

//=========================================================