#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // for each row, col we have a RGBTRIPLE which is just triple of ints.
    // for grayscale we need to loop trhu each pixel and take the avg of the 3 channels and set that number as intensity value for all the 3 channels

    for (int row = 0 ; row < height ;  row++) // for each row of the img
    {
        for (int col = 0 ; col < width ;  col++) // for each row of the img
        {
            float asd = ((image[row][col].rgbtBlue + image[row][col].rgbtGreen + image[row][col].rgbtRed)/3.0);
            image[row][col].rgbtBlue = (int) round(asd);
            image[row][col].rgbtGreen = (int) round(asd);
            image[row][col].rgbtRed = (int) round(asd);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
    // sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
    // sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
    for (int row = 0 ; row < height ;  row++) // for each row of the img
    {
        for (int col = 0 ; col < width ;  col++) // for each row of the img
        {
            float sepiaRed = ((.393*image[row][col].rgbtRed + .769*image[row][col].rgbtGreen + .189 *image[row][col].rgbtBlue));
            float sepiaGreen = ((.349*image[row][col].rgbtRed +  .686*image[row][col].rgbtGreen + .168 *image[row][col].rgbtBlue));
            float sepiaBlue = ((.272*image[row][col].rgbtRed + .534*image[row][col].rgbtGreen + .131 *image[row][col].rgbtBlue));

            image[row][col].rgbtBlue = (int) round(sepiaBlue);
            image[row][col].rgbtGreen = (int) round(sepiaGreen);
            image[row][col].rgbtRed = (int) round(sepiaRed);

            if ((int) round(sepiaBlue)>255)
            {
                image[row][col].rgbtBlue = 255;
            }

            if ((int) round(sepiaGreen)>255)
            {
                image[row][col].rgbtGreen = 255;
            }

            if ((int) round(sepiaRed)>255)
            {
                image[row][col].rgbtRed = 255;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0 ; row < height ; row++)
    {

        // if (width % 2 !=0) // image width is odd
        // {
        int reverse_cols = 1;
        for (int col = 0,  half = width/2; col < half  ; col++)
        {
            int temp_blue = image[row][col].rgbtBlue;
            int temp_green = image[row][col].rgbtGreen;
            int temp_red = image[row][col].rgbtRed;

            // width - reverse_cols since width is the total width, and we start from 0 up to n-1
            image[row][col].rgbtBlue = image[row][width - reverse_cols].rgbtBlue;
            image[row][col].rgbtGreen = image[row][width - reverse_cols].rgbtGreen;
            image[row][col].rgbtRed = image[row][width - reverse_cols].rgbtRed;

            image[row][width - reverse_cols].rgbtBlue = temp_blue;
            image[row][width - reverse_cols].rgbtGreen = temp_green;
            image[row][width - reverse_cols].rgbtRed = temp_red;
            reverse_cols ++;
        }
    }
    return;
}
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int row = 0 ; row < height ;  row++)
    {
    	for (int col = 0 ; col < width ; col++)
    	{
    		if ((row == 0) && (col == 0))
    		{
    			float val_blue = (image[row][col].rgbtBlue + image[row][col+1].rgbtBlue + image[row+1][col].rgbtBlue + image[row+1][col+1].rgbtBlue)/4.0;
                float val_green = (image[row][col].rgbtGreen + image[row][col+1].rgbtGreen + image[row+1][col].rgbtGreen + image[row+1][col+1].rgbtGreen)/4.0;
                float val_red = (image[row][col].rgbtRed + image[row][col+1].rgbtRed + image[row+1][col].rgbtRed + image[row+1][col+1].rgbtRed)/4.0;

                temp[row][col].rgbtBlue = (int) round(val_blue);
                temp[row][col].rgbtGreen = (int) round(val_green);
                temp[row][col].rgbtRed = (int) round(val_red);

    		}

    		else if ((row == 0) && (col == width-1))
    		{
    			float val_blue = (image[row][col].rgbtBlue + image[row][col-1].rgbtBlue + image[row+1][col].rgbtBlue + image[row+1][col-1].rgbtBlue)/4.0;
                float val_green = (image[row][col].rgbtGreen + image[row][col-1].rgbtGreen + image[row+1][col].rgbtGreen + image[row+1][col-1].rgbtGreen)/4.0;
                float val_red = (image[row][col].rgbtRed + image[row][col-1].rgbtRed + image[row+1][col].rgbtRed + image[row+1][col-1].rgbtRed)/4.0;

                temp[row][col].rgbtBlue = (int) round(val_blue);
                temp[row][col].rgbtGreen = (int) round(val_green);
                temp[row][col].rgbtRed = (int) round(val_red);
    		}

    		else if ((row == height - 1) && (col == 0))
    		{
    			float val_blue = (image[row][col].rgbtBlue + image[row-1][col].rgbtBlue + image[row-1][col+1].rgbtBlue + image[row][col+1].rgbtBlue)/4.0;
                float val_green = (image[row][col].rgbtGreen + image[row-1][col].rgbtGreen + image[row-1][col+1].rgbtGreen + image[row][col+1].rgbtGreen)/4.0;
                float val_red = (image[row][col].rgbtRed + image[row-1][col].rgbtRed + image[row-1][col+1].rgbtRed + image[row][col+1].rgbtRed)/4.0;

                temp[row][col].rgbtBlue = (int) round(val_blue);
                temp[row][col].rgbtGreen = (int) round(val_green);
                temp[row][col].rgbtRed = (int) round(val_red);
    		}

    		else if ((row == height - 1) && (col == width-1))
    		{
    			float val_blue = (image[row][col].rgbtBlue + image[row][col-1].rgbtBlue + image[row-1][col].rgbtBlue + image[row-1][col-1].rgbtBlue)/4.0;
                float val_green = (image[row][col].rgbtGreen + image[row][col-1].rgbtGreen + image[row-1][col].rgbtGreen + image[row-1][col-1].rgbtGreen)/4.0;
                float val_red = (image[row][col].rgbtRed + image[row][col-1].rgbtRed + image[row-1][col].rgbtRed + image[row-1][col-1].rgbtRed)/4.0;

                temp[row][col].rgbtBlue = (int) round(val_blue);
                temp[row][col].rgbtGreen = (int) round(val_green);
                temp[row][col].rgbtRed = (int) round(val_red);
    		}

    		else if ((row == 0) && (col != 0) && (col!=width-1))
    		{
    			float val_blue = image[row][col-1].rgbtBlue + image[row][col].rgbtBlue + image[row][col+1].rgbtBlue;
                val_blue = val_blue + image[row+1][col-1].rgbtBlue + image[row+1][col].rgbtBlue + image[row+1][col+1].rgbtBlue;
                val_blue = val_blue/6.0;

                float val_green = image[row][col-1].rgbtGreen + image[row][col].rgbtGreen + image[row][col+1].rgbtGreen;
                val_green = val_green + image[row+1][col-1].rgbtGreen + image[row+1][col].rgbtGreen + image[row+1][col+1].rgbtGreen;
                val_green = val_green/6.0;

                float val_red = image[row][col-1].rgbtRed + image[row][col].rgbtRed + image[row][col+1].rgbtRed;
                val_red = val_red + image[row+1][col-1].rgbtRed + image[row+1][col].rgbtRed + image[row+1][col+1].rgbtRed;
                val_red = val_red/6.0;

                temp[row][col].rgbtBlue = (int) round(val_blue);
                temp[row][col].rgbtGreen = (int) round(val_green);
                temp[row][col].rgbtRed = (int) round(val_red);
    		}

    		else if ((row == height-1) && (col != 0) && (col!=width-1))
    		{
    			float val_blue = image[row-1][col-1].rgbtBlue + image[row-1][col].rgbtBlue + image[row-1][col+1].rgbtBlue;
                val_blue = val_blue + image[row][col-1].rgbtBlue + image[row][col].rgbtBlue + image[row][col+1].rgbtBlue;
                val_blue = val_blue/6.0;

                float val_green = image[row-1][col-1].rgbtGreen + image[row-1][col].rgbtGreen + image[row-1][col+1].rgbtGreen;
                val_green = val_green + image[row][col-1].rgbtGreen + image[row][col].rgbtGreen + image[row][col+1].rgbtGreen;
                val_green = val_green/6.0;

                float val_red = image[row-1][col-1].rgbtRed + image[row-1][col].rgbtRed + image[row-1][col+1].rgbtRed;
                val_red = val_red + image[row][col-1].rgbtRed + image[row][col].rgbtRed + image[row][col+1].rgbtRed;
                val_red = val_red/6.0;

                temp[row][col].rgbtBlue = (int) round(val_blue);
                temp[row][col].rgbtGreen = (int) round(val_green);
                temp[row][col].rgbtRed = (int) round(val_red);
    		}

    		else if ((col == 0) && (row !=0) && (row!=height-1))
    		{
    			float val_blue = image[row-1][col].rgbtBlue + image[row][col].rgbtBlue + image[row+1][col].rgbtBlue;
                val_blue = val_blue + image[row-1][col+1].rgbtBlue + image[row][col+1].rgbtBlue + image[row+1][col+1].rgbtBlue;
                val_blue = val_blue/6.0;

                float val_green = image[row-1][col].rgbtGreen + image[row][col].rgbtGreen + image[row+1][col].rgbtGreen;
                val_green = val_green + image[row-1][col+1].rgbtGreen + image[row][col+1].rgbtGreen + image[row+1][col+1].rgbtGreen;
                val_green = val_green/6.0;

                float val_red = image[row-1][col].rgbtRed + image[row][col].rgbtRed + image[row+1][col].rgbtRed;
                val_red = val_red + image[row-1][col+1].rgbtRed + image[row][col+1].rgbtRed + image[row+1][col+1].rgbtRed;
                val_red = val_red/6.0;


                temp[row][col].rgbtBlue = (int) round(val_blue);
                temp[row][col].rgbtGreen = (int) round(val_green);
                temp[row][col].rgbtRed = (int) round(val_red);
    		}

    		else if ((col == width-1) && (row !=0) && (row!=height-1))
    		{
    			float val_blue = image[row-1][col-1].rgbtBlue + image[row][col-1].rgbtBlue + image[row+1][col-1].rgbtBlue;
                val_blue = val_blue + image[row-1][col].rgbtBlue + image[row][col].rgbtBlue + image[row+1][col].rgbtBlue;
                val_blue = val_blue/6.0;

                float val_green = image[row-1][col-1].rgbtGreen + image[row][col-1].rgbtGreen + image[row+1][col-1].rgbtGreen;
                val_green = val_green + image[row-1][col].rgbtGreen + image[row][col].rgbtGreen + image[row+1][col].rgbtGreen;
                val_green = val_green/6.0;

                float val_red = image[row-1][col-1].rgbtRed + image[row][col-1].rgbtRed + image[row+1][col-1].rgbtRed;
                val_red = val_red + image[row-1][col].rgbtRed + image[row][col].rgbtRed + image[row+1][col].rgbtRed;
                val_red = val_red/6.0;


                temp[row][col].rgbtBlue = (int) round(val_blue);
                temp[row][col].rgbtGreen = (int) round(val_green);
                temp[row][col].rgbtRed = (int) round(val_red);
    		}
    		else
    		{
    			float val_blue = image[row-1][col-1].rgbtBlue + image[row-1][col].rgbtBlue + image[row-1][col+1].rgbtBlue+\
    			                 image[row][col-1].rgbtBlue + image[row][col].rgbtBlue + image[row][col+1].rgbtBlue+\
    			                 image[row+1][col-1].rgbtBlue + image[row+1][col].rgbtBlue + image[row+1][col+1].rgbtBlue;

                float val_green = image[row-1][col-1].rgbtGreen + image[row-1][col].rgbtGreen + image[row-1][col+1].rgbtGreen;
                val_green = val_green + image[row][col-1].rgbtGreen + image[row][col].rgbtGreen + image[row][col+1].rgbtGreen;
                val_green = val_green + image[row+1][col-1].rgbtGreen + image[row+1][col].rgbtGreen + image[row+1][col+1].rgbtGreen;

                float val_red = image[row-1][col-1].rgbtRed + image[row-1][col].rgbtRed + image[row-1][col+1].rgbtRed;
                val_red = val_red + image[row][col-1].rgbtRed + image[row][col].rgbtRed + image[row][col+1].rgbtRed;
                val_red = val_red + image[row+1][col-1].rgbtRed + image[row+1][col].rgbtRed + image[row+1][col+1].rgbtRed;

                val_blue = round(val_blue/9.0);
                val_green = round(val_green/9.0);
                val_red = round(val_red/9.0);

                temp[row][col].rgbtBlue = (int) val_blue;
                temp[row][col].rgbtGreen = (int) val_green;
                temp[row][col].rgbtRed = (int) val_red;
    		}

    	}
    }

    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue ;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed ;
        }
    }

    return;
}
