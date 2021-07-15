#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // validate that there are only two arguments

    if (argc != 2) // prevent user from giving too many or too few arguments; we just want two
    {
        printf("Try again giving one argument made of only letters:\n");
        return 1;
    }

    // validate that key is made of only letters

    string key = argv[1];

    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Make sure your argument contains just letters:\n");
            return 1;
        }
    }

    string plaintext = get_string("plaintext: ");

    string ciphertext = plaintext; // make ciphertext equal to plaintext as its initial state, before enciphering

    int j = 0; // counter for the characters in key

    for (int i = 0, n = strlen(plaintext); i < n; i++) // loop through plaintext and encipher
    {
        if (isalpha(plaintext[i]))  // for each character in plaintext, check if it is a letter
        {
            if (isupper(plaintext[i]))  // check if it is capital letter.
            {
                if (isupper(key[j % strlen(key)])) // check if character j in key is capital letter
                {
                    int alph_in = (int) plaintext[i] - 65; // numeric key of plaintext character i
                    int key_in = (int) key[j % strlen(key)] - 65; // numeric key of key character assigned to plaintext character i
                    int cipher_in = (alph_in + key_in) % 26; // doing the shift
                    ciphertext[i] = (char)(cipher_in + 65); // bringing back to letter
                }
                if (islower(key[j % strlen(key)])) // check if character j in key is lowercase letter
                {
                    int alph_in = (int) plaintext[i] - 65; // numeric key of plaintext character i
                    int key_in = (int) key[j % strlen(key)] - 97; // numeric key of key character assigned to plaintext character i
                    int cipher_in = (alph_in + key_in) % 26; // doing the shift
                    ciphertext[i] = (char)(cipher_in + 65); // bringing back to letter
                }
                j++; // increase key character counter by one
            }  // close if

            else  // if it is a lowercase letter
            {
                if (isupper(key[j % strlen(key)])) // check if character j in key is uppercase letter
                {
                    int alph_in = (int) plaintext[i] - 97; // numeric key of plaintext character i
                    int key_in = (int) key[j % strlen(key)] - 65; // numeric key of key character assigned to plaintext character i
                    int cipher_in = (alph_in + key_in) % 26; // doing the shift
                    ciphertext[i] = (char)(cipher_in + 97); // bringing back to letter
                }
                if (islower(key[j % strlen(key)])) // check if character j in key is lowercase letter
                {
                    int alph_in = (int) plaintext[i] - 97; // numeric key of plaintext character i
                    int key_in = (int) key[j % strlen(key)] - 97; // numeric key of key character assigned to plaintext character i
                    int cipher_in = (alph_in + key_in) % 26; // doing the shift
                    ciphertext[i] = (char)(cipher_in + 97); // bringing back to letter
                }
                j++; // increase key character counter by one

            }  // close else
        }  // close if
    } // close for

    printf("ciphertext: %s", ciphertext);
    printf("\n");
    return 0;
}
