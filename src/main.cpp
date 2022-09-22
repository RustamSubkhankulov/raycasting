#include "../include/logs/logs.h"

//=========================================================

int main()
{
    int err = 0;

    #ifdef LOGS
        open_log_file(Logfile_name);
    #endif 

    // do smth

    #ifdef LOGS
        close_log_file();
    #endif 

    return err;
}