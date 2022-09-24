#pragma once 

//=========================================================

// Light calculation preferences & configuration values

static const unsigned char Alpha_default = 255;

//---------------------------------------------------------

// Sphere preferences

static const Vector Sphere_center_pos{0, 0, 0};

static const Vector Sphere_colour{255, 255, 255}; 

static const double Sphere_rad_sqr = 4;

//---------------------------------------------------------

// Light source preferences

static const Vector Light_src_pos{4, 4, 3  };
static const Vector Light_src_clr{0, 0, 255};

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

    const static Vector Fill_color_rgb{255, 102, 204};
    const unsigned char Fill_color_alpha = 255;

#endif 

//=========================================================

