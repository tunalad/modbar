#include "modules.h"

/* Define your modules here */
static const Module modules[] = {
    /*      FUNCTION        COMMAND             INTERVAL    */
    //{       NULL,           "mb-clock",             1           },
    {       ncs,            NULL,                   1           },
};

/* Redefine if you want to place modbar's named pipe somewhere else */
#define PIPE_PATH "/var/run/user/1000/modbar.pipe"

/* Symbol to separate modules (blank if none) */
#define SEPARATOR "|"
