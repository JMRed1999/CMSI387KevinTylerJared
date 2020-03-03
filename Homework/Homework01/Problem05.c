#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#define FIVE 5

static void *child(void *ignored)
{
  printf("thread dead.\n");
  pthread_cancel(pthread_self());
  return NULL;
}

int main(int argc, char *argv[])
{
  pthread_t child_thread;
  int code;
  char c;

  printf("Hit Enter");
  scanf("%c", &c);
  while ( c == '\n')
  {
    code = pthread_create(&child_thread, NULL, child, NULL);
    sleep(FIVE);
  }
  return 0;
}