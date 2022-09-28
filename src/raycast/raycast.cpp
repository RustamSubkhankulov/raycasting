#include <math.h>
#include <assert.h>

//---------------------------------------------------------

#include "../../include/raycast/raycast.hpp"
#include "../../include/general/general.hpp"

//=========================================================

static Colour calc_components(const Light_src& light_src, const Sphere& sphere, 
                                       Vector& cur_point, Vector& view_point);

//=========================================================

Colour raycast_point(const Scene& scene, const Point_info& point_info)
{
    Colour res{};

    Colour a_comp = A_coeff * (scene.light_src.clr % point_info.colour);
    res += a_comp;

    Vector l = scene.light_src.pos - point_info.coords;
    l.normalize();

    double cos_fi = l * point_info.normal;

    Colour d_comp = (cos_fi < 0)?
                     Colour{} :
                    (cos_fi * D_coeff) * (scene.light_src.clr % point_info.colour);

    res += d_comp;

    Vector l1 = 2 * cos_fi * point_info.normal -  l;
    Vector v  = scene.view_point - point_info.coords;

    double cos_alpha = l1 * v / (l1.len() * v.len()); 
    if (cos_alpha < 0) cos_alpha = 0;
        
    Colour s_comp = pow(cos_alpha, Specular_power) * S_coeff * scene.light_src.clr;
    res += s_comp;

    return res;
}
