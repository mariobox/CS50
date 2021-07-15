#include <stdio.h>
#include <cs50.h>

int main(int argc, char *argv[])
{
    // check that user inputs just one argument
    if (argc != 2)
    {
        fprintf(stderr, "Input one argument!\n");
        return 1;
    }

    // initialize variables
    unsigned char buffer[512];
    char jimage[8];
    int foundJpeg = 0; // switch to indicate if we found our first jpeg
    int counter = 0; // keeps track of how many jpegs we found (starting at 0)

    // set file pointers
    FILE *inptr = fopen(argv[1], "r");
    FILE *outptr = NULL;

    // check for valid data file
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open input file%s.\n", argv[1]);
        return 2;
    }

    // find file size via fseek and then rewind pointer
    fseek(inptr, 0L, SEEK_END);
    int sz = ftell(inptr);
    fseek(inptr, 0L, SEEK_SET);
    rewind(inptr);

    // calculate how many 512 blocks fit in file
    int numOfBlocks = sz / 512;

    // repeat for each 512 byte block until EOF
    for (int i = 0; i < numOfBlocks; i++)
    {
        // read 512 bytes into buffer
        fread(buffer, 1, 512, inptr);

        // check if start of new jpeg
        if
        (
            buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0
        )

        {
            // check if we are reading an existing jpeg
            if (foundJpeg == 1)
            {
                fclose(outptr);
                sprintf(jimage, "%03i.jpg", counter);
                outptr = fopen(jimage, "a");
                fwrite(buffer, 1, 512, outptr);
                counter++;
            }
            // if this is our first jpeg
            else
            {
                foundJpeg = 1;
                sprintf(jimage, "%03i.jpg", counter);
                outptr = fopen(jimage, "a");
                fwrite(buffer, 1, 512, outptr);
                counter++;
            }
        }

        // if we are currently reading a jpeg and current block is not a new jpeg
        else if (foundJpeg == 1)
        {
            fwrite(buffer, 1, 512, outptr);
        }
    }

    // when finished looping over jpegs close open files and end program
    fclose(inptr);
    fclose(outptr);
    return 0;
}