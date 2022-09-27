#pragma once 

//=========================================================

//---------------------------------------------------------

#include "../logs/logs.hpp"
#include "../vector/vector.hpp"
#include "../graphics/graphics.hpp"
#include "../coordsys/coordsys.hpp"
#include "../raycast/raycast.hpp"

//=========================================================

int raycast_sphere_test_( FOR_LOGS(LOG_PARAMS) );

//=========================================================

#define raycast_sphere_test() \
        raycast_sphere_test_( FOR_LOGS(LOG_ARGS))
