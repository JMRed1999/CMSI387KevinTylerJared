#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "goFish.h"

int  main()  
{ 
  /* Read inputs */
  printf("Enter Number: ");  
  for(i = 0; i < LIMIT; i++)  
  {
    scanf("%d", &arr[i]);
    if (arr[i] == EXIT_NUM)
    {
      break;
    }
  }
  int i = 0;
  int j = 1;
  while (arr[i] != EXIT_NUM)
  {
    nums[i] = arr[i];
    i++;
    j++;
  }
  int sum = 0;
  double average = 0;
  strcpy(MAX_CHARS, "");
  /* Calculate sum, average, and concatenate*/
  for(i = 0; i < j-1; i++)  
  {
    sum += nums[i];
    average++;
    sprintf(STRING_TO_NUM, "%d", nums[i]);
    strcat(MAX_CHARS, STRING_TO_NUM);
  }
  /*Count sevens*/
  int SEVEN_COUNT = 0;
  char *check = MAX_CHARS;
	for (k = 0; check[k]; k++)
	{
		if(check[k] == seven)
			SEVEN_COUNT++;
	}
  printf("Sum: %d\nAverage: %f\nInput values: %s\nNumber of Sevens: %d", sum, sum/average, MAX_CHARS, SEVEN_COUNT);
}
