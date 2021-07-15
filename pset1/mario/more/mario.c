#include <cs50.h>
#include <stdio.h>

int main(void)
{
// initialize our pyramid height variable

    int n;

// prompt the user for a pyramid height

    do
    {
        n = get_int("Give me an integer between 0 and 23:\n");
    }
    while (!(n > -1 && n < 24));

// print our pyramid

    for (int i = 0; i < n; i++)
    {

// printing our spaces on left side of pyramid

        for (int j = 0; j < n - (i + 1); j++)
        {
            printf(" ");
        }

// printing our dashes on left side of pyramid

        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }

// printing the gap between left and right side of pyramid

        printf("  ");

// printing our dashes on the right side of pyramid

        for (int l = 0; l < i + 1; l++)
        {
            printf("#");
        }

// moving to the next row

        printf("\n");
    }
}