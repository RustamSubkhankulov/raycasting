#pragma once 

//=========================================================

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

//---------------------------------------------------------

#include "../vector/vector.hpp"
#include "../coordsys/coordsys.hpp"

//=========================================================

// CONFIG

// Text preferences (printing number of axis division)

static const char* Font_filename = "fonts/doom_dont.ttf";

static const unsigned Text_size = 25; //pxls
static const unsigned Text_buf_size = 5;

//=========================================================

namespace Grph
{

enum Style
{
    Titlebar = sf::Style::Titlebar,
    Resize   = sf::Style::Resize,
    Close    = sf::Style::Close,
    Default  = sf::Style::Default,
};

enum Event_type
{
    Closed  = sf::Event::Closed,
    Resized = sf::Event::Resized,
};

enum Mouse_button
{
    Left,
    Right,
    Middle
};

//---------------------------------------------------------

class Window;
class Event;

class Event
{
    sf::Event event_;

    public:

        Event():
            event_()
            {}

        Event_type type(void)
            {
                return (Event_type) event_.type;
            }

    friend class Window;
};

//---------------------------------------------------------

class Window
{
    sf::RenderWindow window_;

    public:

        Window():
            window_()
            {}

        Window(unsigned x_size, unsigned y_size, Style style = Style::Default):
            window_(sf::VideoMode(x_size, y_size), "window", style)
            {}

        bool is_open()
            {
                return window_.isOpen();
            }

        bool get_event(Event& event)
            {
                return window_.pollEvent(event.event_);
            }

        void clear()
            {
                window_.clear(sf::Color::White);
            }

        void close()
            {
                window_.close();
            }

        void display()
            {
                window_.display();
            }

        bool is_mouse_button_pressed(Mouse_button mouse_button);

        Vector get_mouse_pos()
            {
                sf::Vector2i pos = sf::Mouse::getPosition(window_);
                return Vector{(double) pos.x, (double) pos.y};
            }

        void draw(Coordsys& coordsys);
        void draw(const Vector_posed& vectorp, Coordsys& coordsys);

    private:

        void draw_vector_body(const Vector_posed& vectorp, Coordsys& coordsys);
        void draw_vector_ptr (const Vector_posed& vectorp, Coordsys& coordsys);

        void draw_axis_div  (Coordsys& coordsys, Vector_posed& axis, int axis_min);
        void draw_div_number(Coordsys& coordsys, sf::Text& div_num, const Vector& num_point);
};

}; //namespace Grph