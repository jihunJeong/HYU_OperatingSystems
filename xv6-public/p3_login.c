// init: The initial user-level program
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "spinlock.h"

char *argv[] = { "sh", 0 };
char userID[10][20];
char pwdID[10][20];

void get_user_list() {
  //Get User information by reading list.txt
  int fd;

  fd = open("list.txt", O_RDONLY);
  if (fd < 0) {
    //If not exist list.txt, then create it
    fd = open("list.txt", O_RDWR | O_CREATE);
    
    strcpy(userID[0], "root");
    strcpy(pwdID[0], "1234");

    write(fd, userID[0], 20);
    write(fd, pwdID[0], 20);
  } else {
    //Get User and password Information from list.txt
    for(int i=0;i<10;i++) {
      read(fd, userID[i], 20);
      read(fd, pwdID[i], 20);
    }
  }

  close(fd);
}

int check(char* userbuf, char* pwdbuf) {
   //Check ID and Password
  for(int i=0; i < 10; i++) {
    if (strcmp(userID[i], userbuf) == 0 && strcmp(pwdID[i], pwdbuf) == 0) {
      return 0;
    }
  }

  return 1; 
}

int
main(void)
{
  for(;;){
    //Get user Inforamtion
    get_user_list();


    char userbuf[20];
    char pwdbuf[20];

    printf(1, "Username: ");
    gets(userbuf, 20);
    userbuf[strlen(userbuf)-1] = 0;
    printf(1, "Password: ");
    gets(pwdbuf, 20);
    pwdbuf[strlen(pwdbuf)-1] = 0;
    
    if (check(userbuf, pwdbuf)) {
      printf(1, "Wrong login information\n");
      continue;
    }
      //If Input Information is Good, then exectue Shell program
      //setowner(userbuf);
      exec("sh", argv);
      printf(1, "init: exec login failed\n");
      exit();

  }
}
