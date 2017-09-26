#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 1000

int main()
{
  char * token;
  char * ParaArray[100];
  int ParaIndex  = 0;

printf("test\n");
const char* s = getenv("PATH");
printf("PATH :%s\n",(s!=NULL)? s : "getenv returned NULL");
printf("end test\n");

//printf("%c", s[0]);
// We tokenize the user's command and load the tokens into ParaArray
token = strtok(s, " :");
ParaArray[ParaIndex] = token;  ParaIndex++;
while(token != NULL)
  {
    token = strtok(NULL, " :");
    ParaArray[ParaIndex] = token;  ParaIndex++;
  }
ParaArray[ParaIndex]=NULL;
printf("%s\n", ParaArray[0]);

}
