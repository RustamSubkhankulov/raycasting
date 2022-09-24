
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

    const Sphere sphere = {.center_pos = Sphere_center_pos,
                           .colour     = Sphere_colour,
                           .rad_sqr    = Sphere_rad_sqr};

    struct Light_src light_src = {.pos = Light_src_pos,
                                  .clr = Light_src_clr};

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

            if (event.type() == Grph::Event_type::Resized)
            {
                //
            }
        }

        for (unsigned cur_y_pos = 0; cur_y_pos < Wndw_y_size; cur_y_pos++)
        {
            for (unsigned cur_x_pos = 0; cur_x_pos < Wndw_x_size; cur_x_pos++)
            {
                Vector cur_point_r{(double) cur_x_pos, (double) cur_y_pos};
                Vector cur_point = coordsys.reverse_convert_coord(cur_point_r);
                
                // fprintf(stderr, "\n converted: %lf %lf \n", cur_point.x(), cur_point.y());
                // fprintf(stderr, "\n real     : %lf %lf \n", cur_point_r.x(), cur_point_r.y());

                Vector cur_point_rgb = raycast_sphere_point(light_src, sphere, cur_point);

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
    }

    return 0;
}

//---------------------------------------------------------