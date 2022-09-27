#pragma once 

//=========================================================

//---------------------------------------------------------

#include "raycast_conf.hpp"
#include "../logs/logs.hpp"
#include "../vector/vector.hpp"
#include "../colour/colour.hpp"

//=========================================================

struct Light_src
{
    Vector pos{};
    Colour clr{};
};

//---------------------------------------------------------

struct Sphere
{
    Vector center_pos{};
    Colour colour{};
    double rad_sqr = 0;
};

//=========================================================

Colour raycast_sphere_point(const Light_src& light_src, const Sphere& sphere, 
                                     Vector& cur_point, Vector& view_point);
