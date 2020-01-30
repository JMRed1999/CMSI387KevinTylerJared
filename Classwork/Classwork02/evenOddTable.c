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

int main()
{
    int odds = 0;
    int evens = 0;
    for (int i = MIN_INT_VALUE; i <= MAX_INT_VALUE; i++)
    {
        printf("%d\t%d\t%s\n", i, i * i, ((i % 2 == 0)) ? ODD_PARITY : EVEN_PARITY);
        compute_parity(i, &odds, &evens);
    }
    printf("#odd numbers = %d\n#even numbers = %d\n", odds, evens);
    return 0;
}