#pragma once 

//=========================================================

// Light calculation preferences & configuration values

static const unsigned char Alpha_default = 255;

//---------------------------------------------------------

// Sphere preferences

static const double Sphere_center_pos_X = 0;
static const double Sphere_center_pos_Y = 0;
static const double Sphere_center_pos_Z = 0;

static const double Sphere_rad = 3;

//---------------------------------------------------------

// Light source preferences

static const double Light_src_x = 2;
static const double Light_src_y = 2;
static const double Light_src_z = 2;

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
#define FILL_COLOR

#ifdef FILL_COLOR

    const static Vector Fill_color_rgb{153, 255, 102};
    const unsigned char Fill_color_alpha = 255;

#endif 

//=========================================================

