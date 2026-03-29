#include "modules.h"

/* Define your modules here */
static const Module modules[] = {
    /*      FUNCTION                INTERVAL    SIGNAL      */
    {       newsboat_script,        10,         "!newsboat" },
    {       mail_script,            10,         "!mail"     },
    {       tmux_sessions,          1,          NULL        },
    {       ncs,                    1,          NULL        },
    {       datetime,               1,          NULL        },
    {       volume_script,          60,         "!volume"   }, // interval JIC audio breaks
    {       battery_script,         10,         NULL        },
    {       cpu_script,             10,         NULL        },
    {       kb_script,              0,          "!kb"       },
    {       net_script,             5,          NULL        },
};

/* Redefine if you want to place modbar's named pipe somewhere else */
#define PIPE_PATH "/var/run/user/1000/modbar.pipe"

/* Symbol to separate modules (blank if none) */
#define SEPARATOR "|"
