#pragma once 

//=========================================================

//---------------------------------------------------------

#include "raycast_conf.hpp"
#include "../logs/logs.h"
#include "../vector/vector.hpp"

//=========================================================

struct Light_src
{
    Vector pos{};
    Vector clr{};
};

//---------------------------------------------------------

struct Sphere
{
    Vector center_pos{};
    Vector colour{};
    double rad_sqr = 0;
};

//=========================================================

Vector raycast_sphere_point(const Light_src& light_src, const Sphere& sphere, 
                                     Vector& cur_point, Vector& view_point);
