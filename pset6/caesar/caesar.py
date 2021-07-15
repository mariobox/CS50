from cs50 import get_int
from cs50 import get_string
import sys


def main():

    # Convert key to int
    key = int(sys.argv[1])

    # Get input from user
    print("plaintext: ", end='')
    plaintext = get_string()

    # Create new variable for scrambled phrase and put it in array form so we can modify it
    newPhrase = list(plaintext)

    # Capture the length of the text to encypher in new variable
    phraseLen = len(plaintext)

    # Loop through text to encypher
    # Convert character to its ASCII value
    # Convert ASCII value to a 0 to 26 index
    # Add the key
    # Convert back to ASCII
    # Convert back to character
    # Assign to array containing encrypted text

    for i in range(phraseLen):
        if plaintext[i].isalpha():
            if plaintext[i].isupper():
                newPhrase[i] = chr(((ord(plaintext[i]) - 65 + key) % 26 + 65))
            elif plaintext[i].islower():
                newPhrase[i] = chr(((ord(plaintext[i]) - 97 + key) % 26 + 97))

    # Make array into a string
    ciphertext = ''.join(newPhrase)

    # Print encrypted text
    print("ciphertext: ", end='')
    print(ciphertext)


if __name__ == "__main__":
    main()