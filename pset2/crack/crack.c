#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(int args, string argv[])
{
    // initialize variables

    char pass[6] = "";
    char salt [3] = "";
    string abc = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    if (args != 2)
    {
        printf("Please provide a valid hash.\n");
    }

    string hash = argv[1];

    // extract the salt from hash

    for (int i = 0; i < 2; i++)
    {
        salt[i] = argv[1][i];
    }

    // crack one letter passwords

    for (int k = 0, n = strlen(abc); k < n; k++)
    {
        pass[0] = abc[k];
        pass[1] = '\0';
        string temp = crypt(pass, salt);
        if (strcmp(temp, hash) == 0)
            {
                printf("%s\n", pass);
                return 0;
            }
    }

    // crack two letter passwords

    for (int k = 0, n = strlen(abc); k < n; k++)
    {
        for(int l = 0; l < n; l++)
        {
            pass[0] = abc[k];
            pass[1] = abc[l];
            pass[2] = '\0';
            string temp = crypt(pass, salt);
            if (strcmp(temp, hash) == 0)
            {
                printf("%s\n", pass);
                return 0;
            }
        }
    }

    // crack three letter passwords

    for (int k = 0, n = strlen(abc); k < n; k++)
    {
        for (int l = 0; l < n; l++)
        {
            for (int p = 0; p < n; p++)
            {
                pass[0] = abc[k];
                pass[1] = abc[l];
                pass[2] = abc[p];
                pass[3] = '\0';
                string temp = crypt(pass, salt);
                if (strcmp(temp, hash) == 0)
                {
                    printf("%s\n", pass);
                    return 0;
                }
            }
        }
    }

    // crack four letter passwords

    for (int k = 0, n = strlen(abc); k < n; k++)
    {
        for (int l = 0; l < n; l++)
        {
            for (int p = 0; p < n; p++)
            {
                for (int q = 0; q < n; q++)
                {
                    pass[0] = abc[k];
                    pass[1] = abc[l];
                    pass[2] = abc[p];
                    pass[3] = abc[q];
                    pass[4] = '\0';
                    string temp = crypt(pass, salt);
                    if (strcmp(temp, hash) == 0)
                    {
                        printf("%s\n", pass);
                        return 0;
                    }
                }
            }
        }
    }

    // crack five letter passwords

    for (int k = 0, n = strlen(abc); k < n; k++)
    {
        for (int l = 0; l < n; l++)
        {
            for (int p = 0; p < n; p++)
            {
                for (int q = 0; q < n; q++)
                {
                    for (int r = 0; r < n; r++)
                    {
                        pass[0] = abc[k];
                        pass[1] = abc[l];
                        pass[2] = abc[p];
                        pass[3] = abc[q];
                        pass[4] = abc[r];
                        pass[5] = '\0';
                        string temp = crypt(pass, salt);
                        if (strcmp(temp, hash) == 0)
                        {
                            printf("%s\n", pass);
                            return 0;
                        }
                    }
                }
            }
        }
    }

    printf("no luck\n");
}