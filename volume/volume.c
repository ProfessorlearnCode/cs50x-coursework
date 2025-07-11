// Modifies the volume of an audio file
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

typedef int8_t BYTE;
typedef int16_t BYTE2;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    BYTE header[HEADER_SIZE];
    fread(header, sizeof(header), 1, input);
    fwrite(header, sizeof(header), 1, output);


    // TODO: Read samples from input file and write updated data to output file
    BYTE2 buffer;

    // Read single sample from input into buffer
    while(fread(&buffer, sizeof(buffer), 1, input) != 0)
    {
        buffer = (float) buffer;
        // Update volume of sample
        buffer *= factor;

        buffer = (BYTE2) buffer;
        // Write updated sample to new file
        fwrite(&buffer, sizeof(buffer), 1, output);
    }


    // Close files
    fclose(input);
    fclose(output);
}
