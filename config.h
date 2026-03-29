#include "modules.h"

/* Define your modules here */
static const Module modules[] = {
    /*      FUNCTION                INTERVAL    */
    {       newsboat_script,        10      },
    {       mail_script,            10      },
    {       tmux_sessions,          1       },
    {       ncs,                    1       },
    {       datetime,               1       },
    {       volume_script,          1       },
    {       battery_script,         10      },
    {       cpu_script,             10      },
    {       kb_script,              1       },
    {       net_script,             5       },
};

/* Redefine if you want to place modbar's named pipe somewhere else */
#define PIPE_PATH "/var/run/user/1000/modbar.pipe"

/* Symbol to separate modules (blank if none) */
#define SEPARATOR "|"
