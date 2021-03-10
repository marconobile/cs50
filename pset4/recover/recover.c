#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;


int main(int argc, char *argv[])
{

    // Chekc usage:
    if (argc != 2)
    {
        printf("Check for correct usage");
        return 1;
    }

    // Open file: memory card
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Pointing to non existing file");
        return 1;
    }

    int n_of_bytes_read = 512;
    int pic_open;
    FILE *img;
    int first_jpg = 1; // 1 == True
    int jpeg_numb = 0;
    char filename[8]; // need to count also /0

    while (n_of_bytes_read == 512)
    {
        BYTE buffer_512[512];
        n_of_bytes_read = fread(buffer_512, sizeof(BYTE), 512, file);
        // If header:
        if (buffer_512[0] == 0xff && buffer_512[1] == 0xd8 && buffer_512[2] == 0xff && (buffer_512[3] & 0xf0) == 0xe0)
        {
            pic_open = 1;
            if (first_jpg == 1)
            {
                sprintf(filename, "%03i.jpg", jpeg_numb); // check if filename is right
                img = fopen(filename, "w");
                first_jpg = 0;
                fwrite(buffer_512, sizeof(BYTE), n_of_bytes_read, img);
                jpeg_numb++;
            }
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", jpeg_numb);
                img = fopen(filename, "w");
                fwrite(buffer_512, sizeof(BYTE), n_of_bytes_read, img);
                jpeg_numb++;
            }
        }
        else
        {
            if (pic_open == 1)
            {
                fwrite(&buffer_512, sizeof(BYTE), n_of_bytes_read, img);
            }
        }
    }
    fclose(file);
}
