#include <stdio.h>
#include <string.h>
#include <time.h>
#define ARR_SIZE_MODIFIER 215
#define DESIRED_ELEMENT 4096
#define TEN 10

int count;
typedef unsigned char BYTE;

void loop()
{
  int i;
  BYTE arr[DESIRED_ELEMENT*ARR_SIZE_MODIFIER];
  for (i = 0; i < sizeof(arr); i++)
  {
    if ((i != 0) && (i % (DESIRED_ELEMENT-1) == 0))
    {
      count++;
    }
  }
}

int main(void)
{
  int j;
  for (j = 0; j < TEN; j++)
  {
    clock_t begin = clock();
    loop();
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("array access times: %lf\n", time_spent);
    printf("4096th elements accessed: %d\n", count);
  }
  return 0;
}
