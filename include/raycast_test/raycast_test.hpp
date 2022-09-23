#pragma once 

//=========================================================

//---------------------------------------------------------

#include "../logs/logs.h"
#include "../vector/vector.hpp"
#include "../graphics/graphics.hpp"
#include "../coordsys/coordsys.hpp"

//=========================================================

struct Sphere
{
    Vector center_pos{};
    double rad = 0;
};

//=========================================================

int raycast_sphere_test_( FOR_LOGS(LOG_PARAMS) );

//=========================================================

#define raycast_sphere_test() \
        raycast_sphere_test_( FOR_LOGS(LOG_ARGS))
