#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 1000

int exitcmp(char *userCmd) {
  char *ecode = "exit";
  int i;
  int result = 0;
  i = 0;

  //printf("%s\n", userCmd);

    while(ecode[i] == userCmd[i] && result == 0 )
    {
        if(ecode[i] == '\0' || userCmd[i] == '\0'){
            result = 1;
        }
        i++;
    }


    return result;
}

char ** tokenize(char *userCmd1) {
  char * token1;
  char * ParaArray[100];
  //char ** ParaArray;
  int ParaIndex  = 0;

  char ** param;

  token1 = strtok(userCmd1, " \t\n");
  ParaArray[ParaIndex] = token1;
  ParaIndex++;
  while(token1 != NULL)
    {
      token1 = strtok(NULL, " \t\n");
      ParaArray[ParaIndex] = token1;
      ParaIndex++;
    }
  ParaArray[ParaIndex]=NULL;
  //printf("%s\n", ParaArray[0]);

  param = ParaArray;

  return param;
}

int childProcess (char ** paramlist, char* envp[]){
    char *const envParms[2] = {"STEPLIB=SASC.V6.LINKLIB", NULL};
    int status;

    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        //execvp(paramlist[0], paramlist);  // runs word count
        execve(paramlist[0], paramlist, envParms);
        printf("this shouldn't print out");
        //exit(0);
    } else {
        int wc = wait(&status);
        // parent goes down this path (original process)
        //int wc = wait(NULL);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n", rc, wc, (int) getpid());
        exit(1);
    }
    return 0;
}


int main(int argc, char **argv, char* envp[]) {
  int link[2];
  char foo[4096];
  char ** token;
  char ** tokenp;
  char *userCmd = (char *)malloc(sizeof(char) * BUFF_SIZE);
  printf("$");
  fgets(userCmd, BUFF_SIZE+1, stdin);
  token = tokenize(userCmd);
  //tokenp = token;

  //printf("%s\n", token[0]);
  while (exitcmp(token[0]) != 1) {
    //childProcess(token, envp);
    printf("%s\n", token[0]);

    int status;

    //printf("hello world (pid:%d)\n", (int) getpid());
    pid_t pid = fork();
    if (pid < 0) {
      // Failed to fork
      write(STDERR_FILENO, "Failed to fork.\n", 16);
      exit(EXIT_FAILURE);
    } else if (pid == 0) {
      // Child process
      //dup2 (link[1], STDOUT_FILENO);
      //close(link[0]);
      //close(link[1]);
      execve(token[0], token, envp);
      //int nbytes = read(link[0], foo, sizeof(foo));
      //printf("Output: (%.*s)\n", nbytes, foo);
      //write(STDERR_FILENO, "command not found\n", 18);
      exit(EXIT_FAILURE);
    } else {
      // Parent process

      int status;
      wait(&status);

      if (WIFEXITED(status) && WEXITSTATUS(status) < 0) {
        fprintf(stderr, "program terminated with exit code: %d\n", WEXITSTATUS(status));
      }
      //close(link[1]);
      int nbytes = read(link[0], foo, sizeof(foo));
      printf("Output: (%.*s)\n", nbytes, foo);
    }


    printf("$");
    fgets(userCmd, BUFF_SIZE+1, stdin);
    token = tokenize(userCmd);
    //childProcess(token);
    //printf("%s\n", token[0]);
    //int arraysize = sizeof(token)/sizeof(token[0]);
    //printf("%s\n", token[1]);
}

}
