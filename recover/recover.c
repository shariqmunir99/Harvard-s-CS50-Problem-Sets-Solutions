#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./recover Card.raw\n");
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");

    if (inputFile == NULL)
    {
        printf("File Error.\n");
        return 1;
    }

    unsigned char buffer[512];
    int imageCount = 0;

    FILE *outputFile = NULL;

    char *fileName = malloc(8 * sizeof(char));

    while (fread(buffer, sizeof(char), 512, inputFile))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xff) == 0xe0)
        {
            if (imageCount > 0)
            {
                fclose(outputFile);
            }
            sprintf(fileName, "%03i.jpg", imageCount);
            outputFile = fopen(fileName, "w");
            imageCount++;
        }
        if (outputFile != NULL)
        {
            fwrite(buffer, sizeof(char), 512, outputFile);
        }
    }
    free(fileName);
    fclose(outputFile);
    fclose(inputFile);

    return 0;


}