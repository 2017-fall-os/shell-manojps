#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define die(e) do { fprintf(stderr, "%s\n", e); exit(EXIT_FAILURE); } while (0);

extern int errno ;

int main() {
  int errnum;
  int link[2];
  pid_t pid;
  char foo[4096];

  if (pipe(link)==-1)
    die("pipe");

  if ((pid = fork()) == -1)
    die("fork");

  if(pid == 0) {
    //printf("%d\n", pid);
    dup2 (link[1], STDOUT_FILENO);
    close(link[0]);
    close(link[1]);
    int r = execl("/bin/ls", "ls", "-1", (char *)0);
    printf("%d\n", r);
    if (r == -1) {
      perror("error");
      fprintf(stderr, "Value of errno: %d\n", errno);
      if (errno == 2) printf("command not found.\n");
      //errnum = errno;
      //fprintf(stderr, "Error opening file: %s\n", strerror( errnum));
      //strerror(errno);
      //printf("%s\n", typeof(perror("error")));
      //if (typeof(perror("error") == "error: No such file or directory\n") printf("command not found\n" );
    }
    die("execl");

  } else {
    //printf("%d\n", pid);
    //printf("%d\n", link[0]);
    close(link[1]);
    int nbytes = read(link[0], foo, sizeof(foo));
    printf("Output: (%.*s)\n", nbytes, foo);
    wait(NULL);

  }
  return 0;
}
