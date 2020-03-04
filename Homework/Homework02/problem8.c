#include <stdio.h>
#include <string.h>
#include <time.h>
#define ARR_SIZE_MODIFIER 215

int count;
typedef unsigned char BYTE;

void loop()
{
  int i;
  BYTE arr[4096*ARR_SIZE_MODIFIER];
  for (i = 0; i < sizeof(arr); i++)
  {
    if ((i != 0) && (i % 4095 == 0))
    {
      count++;
    }
  }
}

int main(void)
{
  int j;
  for (j = 0; j < 10; j++)
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