#include <stdlib.h>
#include <stdio.h>

#define TOTAL_QUESTIONS 6
#define MAX_CHARS 50

int main()
{
  char user_inputs[TOTAL_QUESTIONS][MAX_CHARS];
  char questions[TOTAL_QUESTIONS][MAX_CHARS] = {
    "What is your name?", "What is your age?", "What is your class year?",
    "What's your favorite movie?", "Who is your favorite artist?", "What are your thoughts on surveys?"};

  for (int i = 0; i < TOTAL_QUESTIONS; i++)
  {
    printf("%s\n", questions[i]);
    gets(user_inputs[i]);
  }

  printf("\nRESULTS:\n");
  for (int i = 0; i < TOTAL_QUESTIONS; i++)
  {
    printf("%s: %s\n", questions[i], user_inputs[i]);
  }

  return 0;
}