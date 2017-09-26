#include <stdio.h>



int scmp(char *input) {
  char *ecode = "exit\n";
  int i;
  int result = 0;
  i = 0;

  printf("%s\n", input);

    while(ecode[i] == input[i] && result == 0 )
    {
        if(ecode[i] == '\0' || input[i] == '\0'){
            result = 1;
        }
        i++;
    }

    return result;
}

int main() {
  int n = 300;
  int r;
  char input[n];
  fgets(input, 300, stdin);
  //printf("%s\n", input);
  //r = scmp(*input);
  if (scmp(input) == 1) printf("Match.\n");
  else printf("Not a match.\n");
  return 0;

}
