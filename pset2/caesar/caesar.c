#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    int n; // initialize the integer value of our key

    if (argc != 2) // prevent user from giving too many or too few arguments; we just want two
    {
        printf("You have to give me just ONE positive integer:\n");
        return 1;
    }

    else
    {
        n = atoi(argv[1]); // convert the key to an integer and storing it in n
    }

    string plaintext = get_string("plaintext: ");

    string ciphertext = plaintext; // make ciphertext equal to plaintext as its initial state, before enciphering

    for (int i = 0, l = strlen(plaintext); i < l; i++) // loop through plaintext and encipher
    {
        if (isalpha(plaintext[i]))  // for each character in plaintext, check if it is a letter
        {
            if (isupper(plaintext[i]))  // check if it is capital letter.
            {
                int alph_in = (int) plaintext[i] - 65;
                int cipher_in = (alph_in + n) % 26;
                ciphertext[i] = (char)(cipher_in + 65);
            }  // close if

            else  // if it is a lowercase letter
            {
                int alph_in = (int) plaintext[i] - 97;
                int cipher_in = (alph_in + n) % 26;
                ciphertext[i] = (char)(cipher_in + 97);
            }  // close else
        }  // close if
    } // close for

    printf("ciphertext: %s", ciphertext);
    printf("\n");
    return 0;
}