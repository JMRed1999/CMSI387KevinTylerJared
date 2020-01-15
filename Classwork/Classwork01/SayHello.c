
#include <stdio.h>
#include <stdlib.h>
#define LIMIT 100

int main(int argc, char *argv[])
{
  char name[LIMIT];

  printf("Enter your name: ");
  gets(name);
  printf("Hello, %s", name);

  return 0;
}
