#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

    uint8_t jpg[4] = {0xff, 0xd8, 0xff, 0xe0}; // Pattern for JPG start
    uint8_t buffer[512];                       // Buffer for reading 512-byte blocks
    int counter = 0;                           // Counter for image file numbering
    char filename[8];                          // Filename for each JPG
    FILE *img = NULL;                          // Pointer to current image file

    // Read 512-byte blocks until end of file
    while (fread(buffer, 1, 512, card) == 512)
    {
        // Check if the block is the start of a new JPG
        if (buffer[0] == jpg[0] && buffer[1] == jpg[1] && buffer[2] == jpg[2] &&
            (buffer[3] & 0xf0) == jpg[3])
        {
            // If already writing an image file, close it
            if (img != NULL)
            {
                fclose(img);
            }

            // Create a new file for the new JPG image
            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");
            if (img == NULL)
            {
                printf("Could not create file %s.\n", filename);
                fclose(card);
                return 1;
            }
            counter++;
        }

        // If an image file is open, write the buffer to it
        if (img != NULL)
        {
            fwrite(buffer, 1, 512, img);
        }
    }

    // Close any remaining open files
    if (img != NULL)
    {
        fclose(img);
    }

    // Close the memory card file
    fclose(card);

    return 0;
}
