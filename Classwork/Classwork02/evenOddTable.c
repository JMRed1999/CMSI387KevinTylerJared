#include <stdio.h>
#include <stdlib.h>
#include "evenOddTable.h"

int compute_parity(int value, int *odds, int *evens)
{
    if (value % 2 == 0)
    {
        *evens += 1;
        return 0;
    }
    *odds += 1;
    return 1;
}

void print_output_line(int value, int squaredValue, int parity)
{
    char *parity_string = ODD_PARITY;
    if (parity == 0)
    {
        parity_string = EVEN_PARITY;
    }
    printf("%d\t%d\t%s\n", value, squaredValue, parity_string);
}

int main()
{
    int odds = 0;
    int evens = 0;
    for (int i = MIN_INT_VALUE; i <= MAX_INT_VALUE; i++)
    {
        print_output_line(i, i * i, compute_parity(i, &odds, &evens));
    }
    printf("#odd numbers = %d\n#even numbers = %d\n", odds, evens);
    return 0;
}