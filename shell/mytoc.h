/* Tokenize input string using specified delimiter */
char ** mytoc(char *str, char delim);

/* Reads input from stdin */
char * user_prompt();

/* Exits the program if exit command is passed through stdin */
int exit_command(char *user_cmd);

/* Count the number of tokens in the input string using the specified delimiter */
int token_count(char *user_in, char delimiter);

/* Number of tokens */
int token_num;
