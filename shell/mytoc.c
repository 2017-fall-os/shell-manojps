#include <stdio.h>
#include <stdlib.h>
#include "mytoc.h"

//  strcopy function was copied from already uploaded code in Github
int tokenCnt;
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

//char **tokenVec;
int tokenCount(char *str, char delim) {
  int flag = 0;
  int token = 0;
  if (*str == '\0') {
    return 0;
  }
  else {
    /* if (*str != ' ' || *str != '\0') { */
  while (1){
    if(flag){
      token++;
      flag = 0;
    }
       if (*str == '\0')
        break;


      while (*str++ != delim){
        //printf("%s\n", str );
        flag = 1;
        continue;
      } //while ((ch = *str++) != ' ' || *str);


  }
  }

  //printf("%d\n", token);
  return token;
}

char ** storeToken(const int size, char *str1, char delim){

  char **tokenVec = NULL;
  //if (*tokenVec != 0) free(tokenVec);
  tokenVec = (char **)calloc(size, sizeof(char *));
  int index = 0;
  while (1){
       if (*str1 == '\0')
        break;

      char *tmpstr = (char*) malloc(sizeof(char));
      int indx = 0;
      char ch = *str1++;
      while ( ch != delim){
        //printf("%s\n", str );
        tmpstr[indx++] = ch;
        ch = *str1++;
        //index++;
        continue;
      } //while ((ch = *str++) != ' ' || *str);

      tmpstr[indx] = '\0';
      //printf("%s\n", tmpstr );
      //if(NULL != tokenVec[index])
            //free(tokenVec[index]);
      tokenVec[index] = calloc(1,sizeof*tmpstr);
      if(tmpstr != NULL){
        tokenVec[index] = strcopy(tmpstr);
        index++;
      }
      //printf("%s\n", tokenVec[0]);
      //if(tmpstr != NULL)
      free(tmpstr);
  }
  for(int i =0; i<size; i++)
      printf("%s\n", tokenVec[i] );
  return tokenVec;
}
/*
void freeMemory()
{
  if(tokenCnt){
    for( int i = 0; i<tokenCnt; i++)
      free(tokenVec[i]);
    free(tokenVec);
  }

}*/

char ** mytoc(char *str2, char delim){
  //char *s1 = "Hello World test ";
  char ** tokenv;
  int tokenNo = tokenCount(str2, delim);
  //printf("%d\n",tokenNo );
  tokenv = storeToken(tokenNo,str2, delim);
  //freeMemory();
  //storeToken(tokenNo,str2, delim);
  tokenCnt = tokenNo;
  //printf("%s\n", tokenv[0]);
  //if(NULL != tokenVec)
    //free(tokenVec);
  return tokenv;
}

/*
int main() {
  char *s1 = "Hello my dog's name is Darwin.";
  mytoc(s1, ' ');
  return 0;
}
*/
