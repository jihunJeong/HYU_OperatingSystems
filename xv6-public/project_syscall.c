#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"

//Project1_syscall
int
sys_yield(void)
{
    
    //Reset Process
    #ifdef MLFQ_SCHED
        struct proc *p = myproc();
        p->level = 0;
        p->quantum = 0;
    #endif
        
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
        return -2;
    return setpriority(pid, priority);
}


//Project2_syscall
int
sys_getadmin(void)
{
    //Get administrator mode System call function by correct password
    
    char* password;

    if(argstr(0, &password) < 0)
        return -1;
    return getadmin(password);
}

int
sys_exec2(void)
{   
    //Get stacksize System call from user argument and set stack page when administrator mode

    char *path, *argv[MAXARG];
    int i, stacksize;
    uint uargv, uarg;

    //When process mode is user mode(1), then return -1
    if(myproc()->mode == 1) {
        return -1;
    }

    if(argstr(0, &path) < 0 || argint(1, (int*)&uargv) < 0 || argint(2, &stacksize)){
        return -1;
    }

    memset(argv, 0, sizeof(argv));
    for(i=0;; i++){
        if(i >= NELEM(argv))
          return -1;
        if(fetchint(uargv+4*i, (int*)&uarg) < 0)
          return -1;
        if(uarg == 0){
          argv[i] = 0;
          break;
        }
        if(fetchstr(uarg, &argv[i]) < 0)
          return -1;
    }

    return exec2(path, argv, stacksize);
}

int
sys_setmemorylimit(void)
{
    //Limit process memory System call by using argument(pid, limit)

    int pid, limit;

    if(argint(0, &pid) < 0 || argint(1, &limit) < 0) {
        return -1;
    }
    
    return setmemorylimit(pid, limit);
}

int
sys_getshmem(void)
{

    int pid;

    if(argint(0, &pid) < 0) {
        return 0;
    }
    return ((uint)getshmem(pid));
}

int
sys_getinfo(void)
{
    return getinfo();
}


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

    if(myproc()->owner != 0) {
        return -1;
    }
    
    if(argstr(0, &username) < 0) {
        return -1;
    }

    return userdel(username);
}
