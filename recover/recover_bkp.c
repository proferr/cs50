#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    uint8_t jpg[4] = {0xff, 0xd8, 0xff, 0xe0};

    uint8_t buffer[512];

    int counter = 0;

    char filename[8];

    while (fread(buffer, 1, 512, card) == 512)
    {

        if (buffer[0] == jpg[0] && buffer[1] == jpg[1] && buffer[2] == jpg[2] && (buffer[3] & 0xf0) == jpg[3])
        {

            printf("END JPG \n");
            printf("START JPG \n");
            sprintf(filename, "%03i.jpg", counter);
            printf("%s\n", filename);
            //FILE *img = fopen(filename, "w");
            counter++;

        }
        else
        {

            printf("%p \n", &buffer);

        }

    }


}
