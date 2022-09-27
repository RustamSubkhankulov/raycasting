
#include <assert.h>

//---------------------------------------------------------

#include "../../include/raycast_test/raycast_test.hpp"
#include "../../include/raycast_test/raycast_test_conf.hpp"
#include "../../include/quadratic_equation/quadratic_equation.hpp"

//=========================================================

static const double Rot_angle_sin = sin(Rot_angle_rad);
static const double Rot_angle_cos = cos(Rot_angle_rad);

//=========================================================

#ifdef FILL_COLOR

    static int pixels_array_fill(Grph::PixelsWindow* window);

#endif 

static void rotate_light(Light_src* light_src);

static void setup_scene(Scene* scene);

static Colour raycast_sphere_point(const Scene& scene, const Vector& cur_point, 
                                                       const Sphere& sphere);

static bool get_straight_sphere_crossing(const Vector& vp, const Vector& straight, 
                                                           const Sphere& sphere, Vector* cross_point);

//=========================================================

#ifdef FILL_COLOR

static int pixels_array_fill(Grph::PixelsWindow* window)
{
    assert(window);

    Vector size = window->get_size();

    unsigned x_size = (unsigned) size.x();
    unsigned y_size = (unsigned) size.y();

    for (unsigned y_pos = 0; y_pos < y_size; y_pos++)
    {
        for (unsigned x_pos = 0; x_pos < x_size; x_pos++)
        {            
            bool is_set = window->set_pixel(x_pos, y_pos, Fill_color_rgb, Fill_color_alpha);
            if (is_set != true)
            {
                error_report(PIXEL_ISNT_SET);
                return PIXEL_ISNT_SET;
            }
        }
    }

    return 0;
}

#endif 

//---------------------------------------------------------

int raycast_sphere_test_( FOR_LOGS(LOG_PARAMS) )
{
    log_report();

    Coordsys coordsys {Coordsys_x_max,
                       Coordsys_x_min,
                       Coordsys_y_max,
                       Coordsys_y_min,
                       Wndw_x_size, 
                       Wndw_y_size};

    coordsys.x_pos = Coordsys_x_pos;
    coordsys.y_pos = Coordsys_y_pos;

    const Sphere sphere = {.center_pos = Sphere_center_pos,
                           .colour     = Sphere_colour,
                           .rad_sqr    = Sphere_rad_sqr};

    Scene scene = {};
    setup_scene(&scene);

    Grph::PixelsWindow window{Wndw_x_size, Wndw_y_size};

    #ifdef FILL_COLOR

        int err = pixels_array_fill(&window);
        if (err)
            return err;

    #endif 

    while (window.is_open())
    {
        Grph::Event event;
        while (window.get_event(event))
        {
            if (event.type() == Grph::Event_type::Closed)
                window.close();
        }

        for (unsigned cur_y_pos = 0; cur_y_pos < Wndw_y_size; cur_y_pos++)
        {
            for (unsigned cur_x_pos = 0; cur_x_pos < Wndw_x_size; cur_x_pos++)
            {
                Vector cur_point_r{(double) cur_x_pos, (double) cur_y_pos};
                Vector cur_point = coordsys.reverse_convert_coord(cur_point_r);
                cur_point.set_z(-Display_plane_d);

                Colour cur_point_rgb = raycast_sphere_point(scene, cur_point, sphere);
                // fprintf(stderr, "%u%u%u\n", cur_point_rgb.get_r(), cur_point_rgb.get_g(), cur_point_rgb.get_b());

                bool is_set = window.set_pixel(cur_point_r, cur_point_rgb, Alpha_default);
                {
                    if (is_set == false)
                    {
                        error_report(PIXEL_ISNT_SET);    
                        return PIXEL_ISNT_SET;
                    }
                }
            }
        }

        window.pixels_update();
        window.pixels_draw();
        
        window.display();

        rotate_light(&scene.light_src);
    }

    return 0;
}

//---------------------------------------------------------

static Colour raycast_sphere_point(const Scene& scene, const Vector& cur_point, 
                                                       const Sphere& sphere)
{
    Vector straight{cur_point - scene.view_point};

    // fprintf(stderr, "cp %lf%lf%lf\n", cur_point.x(), cur_point.y(), cur_point.z());

    Vector cross_point{};
    bool is_cross = get_straight_sphere_crossing(scene.view_point, straight, sphere, &cross_point);
    if (is_cross == false)
        return Colour{};

    // static int iter = 0;
    // if (is_cross)
    // {
    //     fprintf(stderr, "A%d\n", iter++);
    // }
    
    Vector normal = cross_point - sphere.center_pos;
    normal.normalize();

    Point_info point_info = {.normal = normal,
                             .colour = sphere.colour,
                             .coords = cross_point};

    return raycast_point(scene, point_info);
}   

//---------------------------------------------------------

static bool get_straight_sphere_crossing(const Vector& vp, const Vector& straight, 
                                                           const Sphere& sphere, Vector* cross_point)
{
    assert(cross_point);

    // x = v1 + k1 * t = b1 + k1 * t    vi - view_point
    // y = v2 + k1 * t = b2 + k2 * t    ki - straight directional vector 
    // z = v3 + k1 * t = b3 = k3 * t 

    double b1 = vp.x();
    double b2 = vp.y(); 
    double b3 = vp.z();

    double k1 = straight.x(); 
    double k2 = straight.y(); 
    double k3 = straight.x();

    // (k1t + b1 - x0)^2 + (k2t + b2 - y0)^2 + (k3t + b3 - z0)^2 = R^2
    // (k1t + w1)^2 + (k2t + w2)^2 + (k3t + w3)^2 = R^2

    double w1 = b1 - sphere.center_pos.x();
    double w2 = b2 - sphere.center_pos.y();
    double w3 = b3 - sphere.center_pos.z();

    // (k1^2 + k2^2 + k3^2)t^2 + 2 * (k1w1 + k2w2 + k3w3)t + (w1^2 + w2^2 + w3^2 - R^2) = 0

    // double a = k1 * k1 + k2 * k2 + k3 * k3;
    // double b = 2 * (k1 * w1 + k2 * w2 + k3 * w3);
    // double c = w1 * w1 + w2 * w2 + w3 * w3 - sphere.rad_sqr;

    Vector straight_ = straight;
    Vector vp_ = vp;
    double a = straight_.len();
    double b = 2 * (straight_ * vp);
    double c = vp_.len() - sphere.rad_sqr;

    Equation equ = {.a = a, .b = b, .c = c};
    solve_equation(&equ);

    // fprintf(stderr, "%lf\n", b * b - 4 * a * c);

    double t = 0;

    if (equ.roots_ct == ONE_ROOT)
    {
        t = equ.root1;
    }
    else if (equ.roots_ct == TWO_ROOTS)
    {
        t = (equ.root1 > equ.root2)? equ.root2: equ.root1;
    }
    else 
    {
        fprintf(stderr, "A\n");
        return false;
    }

    *cross_point = vp + t * straight;

    // fprintf(stderr, "cp %lf|%lf|%lf\n", cross_point->x(), cross_point->y(), cross_point->z());

    return true;
}

//---------------------------------------------------------

static void setup_scene(Scene* scene)
{
    assert(scene);

    *scene = {.light_src     = {.pos = Light_src_pos, .clr = Light_src_clr},

              .view_point    = View_point};

            //   .display_plane = {.a = Display_plane_a, 
            //                     .b = Display_plane_b,
            //                     .c = Display_plane_c,
            //                     .d = Display_plane_d}};

    return;
}

//---------------------------------------------------------

static void rotate_light(Light_src* light_src)
{
    assert(light_src);

    Vector light_src_pos = light_src->pos;

    Vector rotatable = {light_src_pos.x(), light_src_pos.z()};
    rotatable.rotate_2d_only(Rot_angle_sin, Rot_angle_cos);

    light_src->pos.set(rotatable.x(), light_src_pos.y(), rotatable.y());
}

//---------------------------------------------------------