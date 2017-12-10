#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "mytoc.h"

#define BUFFER 2000 /* Defines user input buffer to be 2000 bytes */

/* global variables */
int token_num = 0; /* Initialize token number */


/* This is the user prompt. It reads the input from stdin, copies the string to
   string, and returns a pointer to the copied string. */

char * user_prompt(){

  char user_command0[BUFFER]; /* Array for user input */
  char *user_command1; /* Pointer to copied string */
  int n = 1;
  int i, j=0;

  /* Reads user input */
  if (n==1) {
    write(1, "$\n", 1);
    n = read(0, user_command0, BUFFER);
  }

  /* Copy user input into a string */
  user_command1 = (char *)malloc(n);
  for(int i = 0; i < n-1; i++){
    user_command1[i] = user_command0[i];
  }
  user_command1[n-1] = '\0';
  
  return user_command1;
}

/* token_count() counts the number of tokens. */
int token_count(char *user_in, char delimiter){
  int token_num = 0;
  int token_flag = 0;
  int i = 0;
  int j = 0;

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
    i++;
  }

  return token_num;
}

/* mytoc() function tokenizes the input string. The input arguments are the po-
   inter to the input string and the delimiter character. The mytoc() function
   returns a pointer to the  token vector. */
char ** mytoc (char *user_str, char delimiter) {

  char **token_vec = (char **)calloc(token_num, sizeof(char *)*token_num); /* Memory allocation for token vector */
  int token_index = 0; /* Initialize token index (current token number) */
  int i = 0; /* Temporary loop control variable */
  int j= 0; /* Temporary loop control variable */
  int m; /* Temporary variable */
  int token_flag = 0; /* Initialize temporary variable token_flag */
  int token_len = 0; /* Initialize temporary variabel token_len */
  int tl[token_num]; /* Temporary array for stroing  tokens */
  int start_index;

  /* Initialize temporary token vector */
  for (m = 0; m < token_num; m++)
  {
  tl[m] = 0;
  }

  /* Traverse the input string until the end */
  while(user_str[i] != '\0')
  {
    /* Extra security in case user input has newline character in the end of
       the string. */
    if (user_str[i] == '\n') break;

    /* Set token_flag and increment token_index when new token starts. Reset
       token_flag when token ends. */
    if (user_str[i] != delimiter && token_flag != 1) {
      token_index++;
      token_flag = 1;
      start_index = i;
    } else if (user_str[i] == delimiter && token_flag == 1) {
      token_flag = 0;
    }

    /* Determine token length for each token. */
    if (token_flag == 1) {
      token_len++;
    } else {
      if (tl[token_index-1] == 0) {
        tl[token_index-1] = token_len;
      }

      if (token_index > 0 && token_flag== 0) {
        token_vec[token_index-1] = (char*) malloc(tl[token_index-1]);
        for (j = 0; j<tl[token_index-1]; j++) {
          token_vec[token_index-1][j] = user_str[start_index+j];
        }
        token_vec[token_index-1][j++] = '\0';
      }
      token_len=0;
    }
    i++;
  }

  /* Gets the correct token at the end of user input if it ends with a null
     terminator. */
  if (user_str[i-1] != delimiter) tl[token_index-1] = token_len;

  /* Write the tokens to the token vector. */
  if (user_str[i] == '\0' || user_str[i] == '\n') {
    token_vec[token_index-1] = (char*) malloc(tl[token_index-1]);
    for (j = 0; j<tl[token_index-1]; j++) {
      token_vec[token_index-1][j] = user_str[start_index+j];
    }
    token_vec[token_index-1][j++] = '\0';
  }
  token_vec[token_index] = NULL; /* Ends the token vector with a null. */

  return token_vec;
}

/* Checks "exit" command in user input. If the "exit" command is found, then it
   terminates the tokenizer. */
int exit_command(char *user_cmd) {
  char *exit_code = "exit\0";
  int i=0, j=0;
  int result = 0;
  
  while(exit_code[i] == user_cmd[i] && result == 0 )
  {
      if(exit_code[i] == '\0' || user_cmd[i] == '\0'){
          result = 1;
      }
      i++;
  }

  return result;
}
