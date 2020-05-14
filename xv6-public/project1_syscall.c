#include "types.h"
#include "defs.h"

int
getlev(void)
{
    return 0;
}

int
setpriority(int pid, int priority)
{
    return 0;
}

int
sys_yield(void)
{
    yield();
    return 0;
}

int
sys_getlev(void)
{
    return getlev();
}

int
sys_setpriority(void)
{
    int pid;
    int priority;

    if(argint(0, &pid) < 0)
        return -1;
    if(argint(1, &priority) < 0)
        return -1;
    return setpriority(pid, priority);
}
