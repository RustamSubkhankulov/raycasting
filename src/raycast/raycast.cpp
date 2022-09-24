#include <math.h>
#include <assert.h>

//---------------------------------------------------------

#include "../../include/raycast/raycast.hpp"
#include "../../include/general/general.hpp"

//=========================================================

static void calculate_z_coord(Vector* point, const Sphere& sphere);


static Vector calc_components(const Light_src& light_src, const Sphere& sphere, 
                                       Vector& cur_point, Vector& view_point);

static Vector rgb_normalize(const Vector& rgb_v);

//=========================================================

Vector raycast_sphere_point(const Light_src& light_src, const Sphere& sphere, 
                                     Vector& cur_point, Vector& view_point)
{
    Vector res{};

    double x = cur_point.x();
    double y = cur_point.y();

    double x0 = sphere.center_pos.x();
    double y0 = sphere.center_pos.y();

    double dist_sqr = (x - x0) * (x - x0) + (y - y0) * (y - y0); 

    if ((dist_sqr < sphere.rad_sqr) || double_is_equal(dist_sqr, sphere.rad_sqr))
    {
        res += calc_components(light_src, sphere, cur_point, view_point);
    }

    return rgb_normalize(res);
}

//---------------------------------------------------------

static Vector calc_components(const Light_src& light_src, const Sphere& sphere, 
                                       Vector& cur_point, Vector& view_point)
{
    Vector res{};

    Vector a_comp = A_coeff * rgb_normalize(light_src.clr % sphere.colour); 
    res += a_comp;

    calculate_z_coord(&cur_point, sphere);

    Vector normal = cur_point - sphere.center_pos;
    normal.normalize();

    Vector l = light_src.pos - cur_point;

    double cos_fi   = l * normal / l.len();
    
    Vector d_comp =  (cos_fi < 0)? 
                      Vector{} : 
                      cos_fi * D_coeff * rgb_normalize(light_src.clr % sphere.colour);
    res += d_comp;

    Vector l1 = 2 * l.len() * cos_fi * normal - l;
    Vector v  = view_point - cur_point;

    double cos_alpha = l1 * v / (l1.len() * v.len()); 
    if (cos_alpha < 0) cos_alpha = 0;
    
    Vector s_comp = (cos_fi < 0) ? 
                     Vector{} :
                     pow(cos_alpha, Glare_power) * S_coeff * light_src.clr;
    
    res += s_comp;

    return res;
}                                                                                                                               

//---------------------------------------------------------

static void calculate_z_coord(Vector* point, const Sphere& sphere)
{
    assert(point);

    double x = point->x();
    double y = point->y();

    double x0 = sphere.center_pos.x();
    double y0 = sphere.center_pos.y();

    double z = sphere.center_pos.z() + sqrt(sphere.rad_sqr - (x - x0) * (x - x0) 
                                                           - (y - y0) * (y - y0));
    point->set_z(z);
    return;
}

//---------------------------------------------------------

static Vector rgb_normalize(const Vector& rgb_v)
{
    double r = rgb_v.x();
    double g = rgb_v.y();
    double b = rgb_v.z();

    if (r > 255) r = 255;
    if (r < 0)   r = 0;

    if (g > 255) g = 255;
    if (g < 0)   g = 0;

    if (b > 255) b = 255;
    if (b < 0)   b = 0;

    return Vector{r, g, b};
}

//---------------------------------------------------------
