#include <stdio.h>

int main() 
{
  char choices1[3][5] = {"sure", "no", "okay?"};


  int a;
  printf("%s\n", "Hey... let's talk");
  printf("%s\n", sizeof(choices1));

  int i;
  
  for (i = 0; i < sizeof(choices1); i++) 
  {
    printf("%lu\n", choices1[i]);
  }
  
  return 0;  
}