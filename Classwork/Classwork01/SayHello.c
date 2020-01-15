#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char name[25];
    printf("Please enter your name below:\n");
    gets(name);
    printf("Hello, %s\n", name);
}

