#pragma once

//=========================================================

#include "../vector/vector.hpp"
#include "../colour/colour.hpp"

//=========================================================

static const unsigned Specular_power = 25;

// diffuse lighting
static const double D_coeff = 0.7;

/// ambient lighting
static const double A_coeff = 0.1;

// specular intensity
static const double S_coeff = 0.7;

//=========================================================

// Light calculation preferences & configuration values

static const unsigned char Alpha_default = 255;

//---------------------------------------------------------

// Sphere preferences

static const Vector Sphere_center_pos{0, 0, 0};
static const Colour Sphere_colour    {304, 0, 210}; 

static const double Sphere_rad_sqr      = 4;

static const double Sphere_y_move_step  = 0.05;

static const double Sphere_y_pos_offset = +1.5;
static const double Sphere_y_neg_offset = -1.5;

//---------------------------------------------------------

// Light source preferences

static const double Rot_angle_rad = (3 * M_PI / 180);

static const Vector Light_src_pos{3, 5, 3};
static const Colour Light_src_clr{255, 255, 255};

static const Vector View_point{0, 0, +6};
static const Vector Plane_v   {0, 0, -4};

//---------------------------------------------------------

// Window & coordsys preferences

static const int Coordsys_x_max = +4;
static const int Coordsys_x_min = -4;

static const int Coordsys_y_max = +4;
static const int Coordsys_y_min = -4;

static const unsigned Coordsys_x_pos = 0;
static const unsigned Coordsys_y_pos = 0;

static const unsigned Wndw_x_size = 800u;
static const unsigned Wndw_y_size = 800u;

//---------------------------------------------------------

// enables filling pixels array with particular value
//#define FILL_COLOR

#ifdef FILL_COLOR

    const static Colour Fill_color_rgb{255, 102, 204};
    const unsigned char Fill_color_alpha = 255;

#endif 

//=========================================================
