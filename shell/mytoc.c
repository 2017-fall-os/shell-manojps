#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "mytoc.h"

#define BUFFER 2000

// global variables
int token_num = 0;

// user input prompt
char * user_prompt(){
  //struct user_input ui;
  char *user_command0;
  char *user_command1;
  int n = 1;
  int i;

  user_command0 = (char *) malloc(sizeof(user_command0));

  if (n==1) {
    write(1, "$\n", 1);
    n = read(0, user_command0, BUFFER);
  }

  //ui.user_command[ui.n-1] = ' ';
  //ui.user_command[ui.n] = '\0';

  //printf("%d\n", ui.n);
  user_command1 = (char *)malloc(n-1);
  //char *pstr = str;

  for(int i = 0; i < n-1; i++){
    user_command1[i] = user_command0[i];
    //printf("%d\n", i);
  }
  //printf("End %d\n", i);
  user_command1[n-1] = '\0';

/*
  for(int i = 0; i < n; i++){
    printf("%02x", user_command1[i]);
  }
  printf("\n");
*/
  return user_command1;
}

// count number of tokens
int token_count(char *user_in, char delimiter){
  int token_num = 0;
  int token_flag = 0;
  int i = 0;

  int j = 0;

  //printf("%s\n", user_in);

  while(user_in[i] != '\0')
  {
    if (user_in[i] == '\n') break;

    if (user_in[i] != delimiter && token_flag != 1) {
      token_num++;
      token_flag = 1;
    } else if (user_in[i] == delimiter && token_flag == 1) {
      token_flag = 0;
    }

    if (token_flag == 1) j++;
    else j=0;
    //printf("char: %c\t token no: %d\t flag: %d\t%d\n", user_in[i], token_num, token_flag, j);
    i++;
  }

  //printf("%d\n", token_num);
  return token_num;
}

// tokenizer function
char ** mytoc (char *user_str, char delimiter) {
//void token_store (int token_num, char *user_str, char delimiter) {
  //char **token_vec = NULL;

  char **token_vec = (char **)calloc(token_num, sizeof(char *)*token_num);
  //token_vec = (char **)calloc(token_num, sizeof(char *)*token_num);
  int token_index = 0;
  int i = 0;
  int j= 0;
  int m;
  int token_flag = 0;
  int token_len = 0;
  int tl[token_num];
  int start_index;

  for (m = 0; m < token_num; m++)
  {
  tl[m] = 0;
  //printf("%d\t%d\n", m, tl[m]);
  }


  while(user_str[i] != '\0')
  {
    if (user_str[i] == '\n') break;

    if (user_str[i] != delimiter && token_flag != 1) {
      token_index++;
      token_flag = 1;
      start_index = i;
      //printf("Start index %d\n", start_index);
    } else if (user_str[i] == delimiter && token_flag == 1) {
      token_flag = 0;
    }

    if (token_flag == 1) {
      token_len++;
    }
    else {
      //printf("%d\n", j);
      if (tl[token_index-1] == 0) {
        tl[token_index-1] = token_len;
      }

      if (token_index > 0 && token_flag== 0) {
        token_vec[token_index-1] = (char*) malloc(tl[token_index-1]);
        for (j = 0; j<tl[token_index-1]; j++) {
          //token_vec[token_index-1][j] = user_str[i-tl[token_index-1]+j];
          token_vec[token_index-1][j] = user_str[start_index+j];
        }
        token_vec[token_index-1][j++] = '\0';
      }
      //printf("%d\n", tl[token_index-1]);
      //printf("%s\n", );
      token_len=0;
    }
    //printf("char: %c\t token no: %d\t flag: %d\t%d\n", user_str[i], token_index, token_flag, j);
    i++;
  }

  //printf("%d\t%d\n", j, token_index);
  if (user_str[i-1] != delimiter) tl[token_index-1] = token_len;

  //for (k=0; k<token_num; k++) printf("%d\t%d\n", k, tl[k]);

  if (user_str[i] == '\0' || user_str[i] == '\n') {
    token_vec[token_index-1] = (char*) malloc(tl[token_index-1]);
    for (j = 0; j<tl[token_index-1]; j++) {
      //token_vec[token_index-1][j] = user_str[i-tl[token_index-1]+j];
      token_vec[token_index-1][j] = user_str[start_index+j];
    }
    token_vec[token_index-1][j++] = '\0';
  }

  token_vec[token_index] = NULL;

  return token_vec;
}

// program exit
int exit_command(char *user_cmd) {
  char *exit_code = "exit";
  int i=0;
  int result = 0;

  //printf("EXIT FUNC\n");


  while(exit_code[i] == user_cmd[i] && result == 0 )
  {
      //printf("%02x\t%02x\n", exit_code[i], user_cmd[i]);
      if(exit_code[i] == '\0' || user_cmd[i] == '\0'){
          result = 1;
      }
      i++;
  }
  printf("\n");

  return result;
}
