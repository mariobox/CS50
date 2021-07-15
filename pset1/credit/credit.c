#include <cs50.h>
#include <stdio.h>


// create power function that we will use in our main function

long long pwr(long long x, int y)
{
    long long res = 1;
    for (int i = 1; i <= y; i++)
    {
        res *= x;
    }
    return res;
} // close pwr function

// start main function

int main(void)
{

// initialize variable to hold card number
    long long n;

// get input from user and validate that input is a positive integer
    do
    {
        n = get_long_long("cc number:\n");
    }
    while (!(n > 0 && n <= 9999999999999999));

// calculate the number of digits in the card
    int l = 0;
    while (n / pwr(10, l) > 0)
    {
        l++;
    } // close while

// find if card number is a valid credit card number
    // initialize variables

    int sum1 = 0;
    int sum2 = 0;
    long long temp_n = n;
    int temp_m = 0;

    // run validation formula

    for (int counter = 1; counter <= l; counter++)
    {
        if (counter % 2 != 0)
        {
            sum1 = sum1 + temp_n % 10;
            temp_n = temp_n / 10;
        } // close if
        else
        {
            temp_m = 2 * (temp_n % 10);
            if (temp_m % 10 == temp_m)
            {
                sum2 = sum2 + temp_m;
                temp_n = temp_n / 10;
            } // close if
            else
            {
                sum2 = sum2 + temp_m / 10 + temp_m % 10;
                temp_n = temp_n / 10;
            } // close else
        } // close else
    } // close for

// if last digit is 0 then find out if card number matches any of the major companies

    if ((sum1 + sum2) % 10 == 0)
    {

        // checking for companies that use 16 digits

        if (l == 16)
        {
            if (n / pwr(10, 15) == 4)
            {
                printf("VISA\n");
            }

            else
            {
                switch (n / pwr(10, 14))
                {
                    case 51 :
                        printf("MASTERCARD\n");
                        break;
                    case 52 :
                        printf("MASTERCARD\n");
                        break;
                    case 53:
                        printf("MASTERCARD\n");
                        break;
                    case 54:
                        printf("MASTERCARD\n");
                        break;
                    case 55:
                        printf("MASTERCARD\n");
                        break;
                    default:
                        printf("INVALID\n");
                        break;
                } // close switch
            } // close else
        }    // close if

        // checking for companies that use 13 digits

        if (l == 13)
        {
            switch (n / pwr(10, 12))
            {
                case 4:
                    printf("VISA\n");
                    break;
                default:
                    printf("INVALID\n");
                    break;
            } // close switch
        }  // close if

        // checking for companies that use 15 digits

        if (l == 15)
        {
            switch (n / pwr(10, 13))
            {
                case 34:
                    printf("AMEX\n");
                    break;
                case 37:
                    printf("AMEX\n");
                    break;
                default:
                    printf("INVALID\n");
                    break;
            } // close switch
        }  // close if

        // flag numbers with less than 13  or equal to 14 digits as invalid

        if (l < 13 || l == 14)
        {
            printf("INVALID\n");
        } // close if
    } // close if

// if card doesn't belong to any of the major companies flag as invalid

    else
    {
        printf("INVALID\n");
    } // close else

} // close main

