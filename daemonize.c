#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/* fork from parent */
void
daemonize(void)
{
  pid_t pid, sid;
  pid = fork(); 
 
 if (pid < 0) {
    /* fork didn't work, kill parent */
    exit(EXIT_FAILURE);
  }
  if (pid > 0) {
    /* fork worked, kill parent */
    exit(EXIT_SUCCESS); 
  }
  
  /* change the process mask so it can access fs */
  umask(0);
  
  /* request session id for child */
  sid = setsid();
  if (sid < 0) {
    /* exit if it didn't work */
    exit(EXIT_FAILURE); 
  }
  
  if((chdir("/")) < 0) {
    /* exit if it didn't work */ 
    exit(EXIT_FAILURE);
  }
  
  close(STDIN_FILENO);
  close(STDERR_FILENO);
  //close(STDOUT_FILENO);
}
