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

struct Display_plane // a * x + b * y + c * z + d = 0
{
    double a = 0;
    double b = 0;
    double c = 0;
    double d = 0;
};

//---------------------------------------------------------

struct Scene
{
    Light_src     light_src    {};
    Vector        view_point   {};
    // Display_plane display_plane{};
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
