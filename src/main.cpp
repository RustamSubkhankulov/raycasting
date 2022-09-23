#include "../include/logs/logs.h"
#include "../include/raycast_test/raycast_test.hpp"

//=========================================================

int main()
{
    int err = 0;

    #ifdef LOGS
        open_log_file(Logfile_name);
    #endif 

    err = raycast_sphere_test();

    #ifdef LOGS
        close_log_file();
    #endif 

    return err;
}