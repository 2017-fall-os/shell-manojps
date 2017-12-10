#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "mytoc.h"

#define BUFF_SIZE 2000

char *strcopy(char *inStr)	/* like strdup */
{
  char *pStr, *copy, *pCopy;
  size_t len;
  for (pStr = inStr; *pStr; pStr++) // count # chars in str
    ;
  len = pStr - inStr + 1;
  copy = pCopy = (char *)malloc(len); // allocate memory to hold  copy 
  for (pStr = inStr; *pStr; pStr++) // duplicate 
    *(pCopy++) = *pStr;
  *pCopy = 0;			// terminate copy 
  return copy;
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
        execve("/bin/ls", paramlist, envp);

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
  //int pipes[2];
  //char buf[4096];
  char ** token;
  char ** tokenpath;
  //char *userCmd = (char *)malloc(sizeof(char) * BUFF_SIZE);
  char * env, *com_path;
  char *full_path;
  char *user_command;
  int i,j, env_token_num;


  struct stat *file_stat;

  env = getenv("PATH");
  //printf("%s\n", env);

  //pipe(pipes);

  //printf("%s\n", getenv("PATH"));
  //printf("%s\n", getenv("HOME"));
  //char cwd[1024];
  //if (getcwd(cwd, sizeof(cwd)) != NULL) printf("%s\n", cwd);
  
  token_num = token_count(env, ':');
  env_token_num = token_num;
  tokenpath = mytoc(env, ':');
  //for (i=0; i<token_num; i++) printf("argv[%d] = %s\n", i, tokenpath[i]);
  //printf("%s\n", tokenpath[2]);

  while (1) {
    int com_found = 0;
    user_command = user_prompt();
    token_num = token_count(user_command, ' ');
    token = mytoc(user_command, ' ');
    //for (i=0; i<token_num; i++) printf("argv[%d] = %s\n", i, token[i]);
    if (exit_command(user_command)) return 0;
    
    if (token_num>0) {
      for (j=0; j<env_token_num; j++) {
        //full_path = tokenpath[j];
        //strcpy(full_path,tokenpath[j]);
        full_path = strcopy(tokenpath[j]);
        strcat(full_path,"/"); // Using C library function
        strcat(full_path,token[0]);
        //printf("%s\n", full_path);
        file_stat = malloc(sizeof(struct stat));
        //int exist = stat(full_path,&file_stat);
        //fprintf(stdout, "File exist: %d\n", exist);
        
        //if(stat(full_path,&file_stat) == 0) {
        if(stat(full_path,file_stat) == 0) {
          com_found = 1;
          ///strcpy(com_path, full_path);
          com_path = strcopy(full_path);
          write(1, "Verified command exist. After strcpy\n", 38);
          //printf("%s\n", com_path);l
          //printf("%s\n", full_path);
          free(file_stat);
          break;
        }
        
        free(file_stat);

      }

      if (com_found == 0) write(1, "command not found.\n",20);
      else {
        pid_t pid;
        
        pid = fork();
        
        if (pid == 0) {
          execve(com_path, token, envp);
          exit(0);
        } else {
          int status;
          waitpid(pid, &status, 0);
        }
        
      }

    }
    //free(full_path);
    //free(tokenpath);
    free(token);
  }
  
  free(tokenpath);
  free(full_path);
  

  return 0;
}
