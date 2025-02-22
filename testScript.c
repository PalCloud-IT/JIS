#include <stdio.h>

//#define 

int main() 
{
  int a = 3;
  int b = 5;
  char choices1[3][5] = {"Sure", "no", "okay?"};
  char firstUserResponse[30];

  printf("%s\n", "Hey... let's talk \n");
  scanf("%s", &firstUserResponse);
  printf("User response: %s", firstUserResponse);
  //int i;
  //int j;
  
  for (int i = 0; i < 3; i++) 
  {
    printf("%i", i + 1);
    printf("%s", ". ");
    printf("%s\n", choices1[i]);
  }

  return 0;  
}