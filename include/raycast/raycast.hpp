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

struct Scene
{
    Light_src     light_src    {};
    Vector        view_point   {};
    Vector        plane        {};
};


//---------------------------------------------------------

struct Sphere
{
    Vector center_pos{};
    Colour colour{};
    double rad_sqr = 0;
};

//---------------------------------------------------------

struct Point_info
{
    Vector normal{};
    Colour colour{};
    Vector coords{};
};

//=========================================================

Colour raycast_point(const Scene& scene, const Point_info& point_info);
