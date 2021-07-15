#include <stdio.h>
#include <cs50.h>
#include <math.h>


int main(void)
{
    // initialize change variable in global scope to be used later
    float change;

    // prompt user for a valid amount
    do
    {
        change = get_float("How much change do you need?\n");
    }
    while (change < 0);

    // translate the amount of change owed into cents
    int change_cent = round(change *= 100);

    // initialize the number of coins to zero
    int num_coins = 0;

    // find out how many 25 cent coins we need to give
    if (change_cent >= 25)
    {
        num_coins = num_coins + change_cent / 25;
        // recalculate the remaining change after giving 25 cent coins
        change_cent = change_cent % 25;
    }

    // find out how many 10 cent coins we need to give
    if (change_cent >= 10)
    {
        num_coins = num_coins + change_cent / 10;
        // recalculate the remaining change after giving 10 cent coins
        change_cent = change_cent % 10;
    }

    // find out how many 5 cent coins we need to give
    if (change_cent >= 5)
    {
        num_coins = num_coins + change_cent / 5;
        // recalculate the remaining change after giving 5 cent coins
        change_cent = change_cent % 5;
    }

    // find out how many 1 cent coins we need to give
    if (change_cent >= 1)
    {
        num_coins = num_coins + change_cent;
        // recalculate the remaining change. If everything went well it should be zero
        change_cent = change_cent % 1;
    }

    // print the number of coins given
    printf("%i\n", num_coins);

}