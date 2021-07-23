#include<stdio.h>
#include <string.h>
#include<stdlib.h>

void calculate (char* string[])
{
  int sum;
  char*  token = strtok(string, "+");
  sum =0;
  while( token != NULL ) {
      sum = sum + atoi(token);
     token = strtok(NULL, "+");
  }

  sprintf(string, "%d", sum);
}
