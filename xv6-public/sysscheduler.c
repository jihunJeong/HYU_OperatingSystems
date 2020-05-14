#include "types.h"
#include "defs.h"


void
sys_yield(void)
{
  cprintf("check yield");
}

int
sys_getlev(void)
{
  cprintf("check getlev");
  return 0;
}

int
sys_setpriority(void)
{
  int pid, priority;

  argint(0, &pid);
  argint(1, &priority);
  cprintf("check setpriority");
  return 0;
}
