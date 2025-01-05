#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ciphertext(string plaintext, int key);

int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument
    if (argc != 2)
    {
        printf("Cant be Ciphered\n");
        return 1;
    }
    else
    {
        // Make sure every character in argv[1] is a digit
        string key = argv[1];
        for (int i = 0; i < strlen(key); i++)
        {
            if (isdigit(key[i]) == 0)
            {
                printf("Usage: ./caesar key(number)\n");
                return 1;
            }
        }
    }

    // Convert argv[1] from a `string` to an `int`
    int key = atoi(argv[1]);

    // Prompt user for plaintext
    string plaintext = get_string("Plaintext: ");

    printf("Ciphertext: ");

    ciphertext(plaintext, key);

    printf("\n");
}

// For each character in the plaintext:
void ciphertext(string plaintext, int key)
{
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                printf("%c", ((plaintext[i] - 'A' + key) % 26) + 'A');
            }
            else if (islower(plaintext[i]))
            {
                printf("%c", ((plaintext[i] - 'a' + key) % 26) + 'a');
            }
        }
        else
        {
            printf("%c", plaintext[i]);
        }

    }
}
