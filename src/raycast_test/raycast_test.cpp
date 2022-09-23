
#include <assert.h>

//---------------------------------------------------------

#include "../../include/raycast_test/raycast_test.hpp"
#include "../../include/raycast_test/raycast_test_conf.hpp"

//=========================================================

#ifdef FILL_COLOR

    static int pixels_array_fill(Grph::PixelsWindow* window);

#endif 

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

    const Sphere sphere = {.center_pos = Vector{Sphere_center_pos_X, 
                                                Sphere_center_pos_Y, 
                                                Sphere_center_pos_Z}, 
                           .rad = Sphere_rad};
    const double sphere_rad_sqr = sphere.rad * sphere.rad;

    Vector light_pos{Light_src_x, Light_src_y, Light_src_z};

    Grph::PixelsWindow window{Wndw_x_size, Wndw_y_size};

    #ifdef FILL_COLOR

        int err = pixels_array_fill(&window);
        if (err)
            return err;

    #endif 

    unsigned cur_x_pos = 0;
    unsigned cur_y_pos = 0;

    while (window.is_open())
    {
        Grph::Event event;
        while (window.get_event(event))
        {
            if (event.type() == Grph::Event_type::Closed)
                window.close();

            if (event.type() == Grph::Event_type::Resized)
            {
                //
            }

            Vector cur_point = coordsys.reverse_convert_coord(Vector{(double) cur_x_pos, 
                                                                     (double) cur_y_pos});
            
            Vector cur_point_rgb{};

            if (cur_point.x() * cur_point.x() + cur_point.y() * cur_point.y() <= sphere_rad_sqr)
            {
                cur_point_rgb.set(255, 255, 255); //white
            }
            else 
            {
                cur_point_rgb.set(0, 0, 0); //black
            }

            bool is_set = window.set_pixel(cur_point, cur_point_rgb, Alpha_default);
            {
                if (is_set != 0)
                {
                    error_report(PIXEL_ISNT_SET);
                    
                    continue;  // <- temporary
                    
                    //return PIXEL_ISNT_SET;
                }
            }

            // Vector size_v = window.get_size();

            Vector size_v = Vector {Wndw_x_size, Wndw_y_size}; // <- temporary

            if (cur_x_pos == size_v.x() - 1)
            {
                cur_x_pos = 0;
                cur_y_pos = (cur_y_pos == size_v.y() - 1)? 0: cur_y_pos + 1;
            }
            else
            {
                cur_x_pos += 1;
            }
        }
    }

    return 0;
}