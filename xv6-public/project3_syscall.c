#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"

//Project3_syscall
int
sys_useradd(void)
{
    char *username;
    char *password;
    
    if(strncmp(myproc()->owner, "root", 20) != 0) {
        return -1;
    }

    if(argstr(0, &username) < 0 || argstr(0, &password) < 0) {
        return -1;
    }

    return useradd(username, password);
}

int
sys_userdel(void)
{
    char *username;

    if(strncmp(myproc()->owner, "root", 20) != 0) {
        return -1;
    }
    
    if(argstr(0, &username) < 0) {
        return -1;
    }

    return userdel(username);
}

int
sys_setowner(void)
{
    return 0;
    /*
    char *username;

    if(argstr(0, &username) < 0) {
        return -1;
    }

    return setowner(username);
    */
}
