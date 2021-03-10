#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
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

// Blur image
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

void edges(int height, int width, RGBTRIPLE image[height][width])
{
	float dx[3][3];
	dx[0][0] = -1.0;
	dx[0][1] = 0.0;
	dx[0][2] = 1.0;
	dx[1][0] = -2.0;
	dx[1][1] = 0.0;
	dx[1][2] = 2.0;
	dx[2][0] = -1.0;
	dx[2][1] = 0.0;
	dx[2][2] = 1.0;

	float dy[3][3];
	dy[0][0] = -1.0;
	dy[0][1] = -2.0;
	dy[0][2] = -1.0;
	dy[1][0] = 0.0;
	dy[1][1] = 0.0;
	dy[1][2] = 0.0;
	dy[2][0] = 1.0;
	dy[2][1] = 2.0;
	dy[2][2] = 1.0;

	float RED_pix_x, RED_pix_y, RED_pix_x_squared, RED_pix_y_squared;
	float GREEN_pix_x, GREEN_pix_y, GREEN_pix_x_squared, GREEN_pix_y_squared;
	float BLUE_pix_x, BLUE_pix_y, BLUE_pix_x_squared, BLUE_pix_y_squared;
	int val_temp;

	RGBTRIPLE temp[height][width];
	for (int row = 0 ; row < height ; row++)
	{
		for (int col = 0 ; col < width ; col++)
		{
			// temp.i(r,c) = (int) round(sqrt((conv2d_x(r,c))**2 (conv2d_y(r,c))**2))

			if ((row == 0) && (col == 0))
			{
				/// RED (0,0)
				RED_pix_x = dx[1][1]*image[row][col].rgbtRed + dx[1][2]*image[row][col+1].rgbtRed + dx[2][1]*image[row+1][col].rgbtRed + dx[2][2]*image[row+1][col+1].rgbtRed;
				RED_pix_y = dy[1][1]*image[row][col].rgbtRed + dy[1][2]*image[row][col+1].rgbtRed + dy[2][1]*image[row+1][col].rgbtRed + dy[2][2]*image[row+1][col+1].rgbtRed;

				RED_pix_x_squared = powf(RED_pix_x, 2.0);
				RED_pix_y_squared = powf(RED_pix_y, 2.0);

				val_temp = (int) round(sqrt(RED_pix_x_squared + RED_pix_y_squared));

				if (val_temp >= 255)
				{
					temp[row][col].rgbtRed = 255;
				}
				else
				{
					temp[row][col].rgbtRed = (int) round(sqrt(RED_pix_x_squared + RED_pix_y_squared));
				}

				/// GREEN (0,0)
				GREEN_pix_x = dx[1][1]*image[row][col].rgbtGreen + dx[1][2]*image[row][col+1].rgbtGreen + dx[2][1]*image[row+1][col].rgbtGreen + dx[2][2]*image[row+1][col+1].rgbtGreen;
				GREEN_pix_y = dy[1][1]*image[row][col].rgbtGreen + dy[1][2]*image[row][col+1].rgbtGreen + dy[2][1]*image[row+1][col].rgbtGreen + dy[2][2]*image[row+1][col+1].rgbtGreen;

				GREEN_pix_x_squared = powf(GREEN_pix_x, 2.0);
				GREEN_pix_y_squared = powf(GREEN_pix_y, 2.0);

				val_temp = (int) round(sqrt(GREEN_pix_x_squared + GREEN_pix_y_squared));

				if (val_temp >= 255)
				{
					temp[row][col].rgbtGreen = 255;
				}
				else
				{
					temp[row][col].rgbtGreen = (int) round(sqrt(GREEN_pix_x_squared + GREEN_pix_y_squared));
				}


				/// BLUE (0,0)
				BLUE_pix_x = dx[1][1]*image[row][col].rgbtBlue + dx[1][2]*image[row][col+1].rgbtBlue + dx[2][1]*image[row+1][col].rgbtBlue + dx[2][2]*image[row+1][col+1].rgbtBlue;
				BLUE_pix_y = dy[1][1]*image[row][col].rgbtBlue + dy[1][2]*image[row][col+1].rgbtBlue + dy[2][1]*image[row+1][col].rgbtBlue + dy[2][2]*image[row+1][col+1].rgbtBlue;

				BLUE_pix_x_squared = powf(BLUE_pix_x, 2.0);
				BLUE_pix_y_squared = powf(BLUE_pix_y, 2.0);

				val_temp = (int) round(sqrt(BLUE_pix_x_squared + BLUE_pix_y_squared));

				if (val_temp >= 255)
				{
					temp[row][col].rgbtBlue = 255;
				}
				else
				{
					temp[row][col].rgbtBlue = (int) round(sqrt(BLUE_pix_x_squared + BLUE_pix_y_squared));
				}
			}

			if ((row == 0) && (col == width - 1))
			{
				// RED(0,N)
				RED_pix_x = dx[1][1]*image[row][col].rgbtRed + dx[1][0]*image[row][col-1].rgbtRed + dx[2][1]*image[row+1][col].rgbtRed + dx[2][0]*image[row+1][col-1].rgbtRed;
				RED_pix_y = dy[1][1]*image[row][col].rgbtRed + dy[1][0]*image[row][col-1].rgbtRed + dy[2][1]*image[row+1][col].rgbtRed + dy[2][0]*image[row+1][col-1].rgbtRed;

				RED_pix_x_squared = powf(RED_pix_x, 2.0);
				RED_pix_y_squared = powf(RED_pix_y, 2.0);

				val_temp = (int) round(sqrt(RED_pix_x_squared + RED_pix_y_squared));

				if (val_temp >= 255)
				{
					temp[row][col].rgbtRed = 255;
				}
				else
				{
					temp[row][col].rgbtRed = (int) round(sqrt(RED_pix_x_squared + RED_pix_y_squared));
				}


				// GREEN(0,N)
				GREEN_pix_x = dx[1][1]*image[row][col].rgbtGreen + dx[1][0]*image[row][col-1].rgbtGreen + dx[2][1]*image[row+1][col].rgbtGreen + dx[2][0]*image[row+1][col-1].rgbtGreen;
				GREEN_pix_y = dy[1][1]*image[row][col].rgbtGreen + dy[1][0]*image[row][col-1].rgbtGreen + dy[2][1]*image[row+1][col].rgbtGreen + dy[2][0]*image[row+1][col-1].rgbtGreen;

				GREEN_pix_x_squared = powf(GREEN_pix_x, 2.0);
				GREEN_pix_y_squared = powf(GREEN_pix_y, 2.0);

				val_temp = (int) round(sqrt(GREEN_pix_x_squared + GREEN_pix_y_squared));

				if (val_temp >= 255)
				{
					temp[row][col].rgbtGreen = 255;
				}
				else
				{
					temp[row][col].rgbtGreen = (int) round(sqrt(GREEN_pix_x_squared + GREEN_pix_y_squared));
				}

				// BLUE(0,N)
				BLUE_pix_x = dx[1][1]*image[row][col].rgbtBlue + dx[1][0]*image[row][col-1].rgbtBlue + dx[2][1]*image[row+1][col].rgbtBlue + dx[2][0]*image[row+1][col-1].rgbtBlue;
				BLUE_pix_y = dy[1][1]*image[row][col].rgbtBlue + dy[1][0]*image[row][col-1].rgbtBlue + dy[2][1]*image[row+1][col].rgbtBlue + dy[2][0]*image[row+1][col-1].rgbtBlue;

				BLUE_pix_x_squared = powf(BLUE_pix_x, 2.0);
				BLUE_pix_y_squared = powf(BLUE_pix_y, 2.0);

				val_temp = (int) round(sqrt(BLUE_pix_x_squared + BLUE_pix_y_squared));

				if (val_temp >= 255)
				{
					temp[row][col].rgbtBlue = 255;
				}
				else
				{
					temp[row][col].rgbtBlue = (int) round(sqrt(BLUE_pix_x_squared + BLUE_pix_y_squared));
				}

			}

			if ((row == height-1) && (col == 0))
			{
				// RED
				RED_pix_x = dx[1][1]*image[row][col].rgbtRed + dx[1][2]*image[row][col+1].rgbtRed + dx[0][1]*image[row-1][col].rgbtRed + dx[0][2]*image[row-1][col+1].rgbtRed;
				RED_pix_y = dy[1][1]*image[row][col].rgbtRed + dy[1][2]*image[row][col+1].rgbtRed + dy[0][1]*image[row-1][col].rgbtRed + dy[0][2]*image[row-1][col+1].rgbtRed;

				RED_pix_x_squared = powf(RED_pix_x, 2.0);
				RED_pix_y_squared = powf(RED_pix_y, 2.0);

				val_temp = (int) round(sqrt(RED_pix_x_squared + RED_pix_y_squared));

				if (val_temp >= 255)
				{
					temp[row][col].rgbtRed = 255;
				}
				else
				{
					temp[row][col].rgbtRed = (int) round(sqrt(RED_pix_x_squared + RED_pix_y_squared));
				}


				// GREEN
				GREEN_pix_x = dx[1][1]*image[row][col].rgbtGreen + dx[1][2]*image[row][col+1].rgbtGreen + dx[0][1]*image[row-1][col].rgbtGreen + dx[0][2]*image[row-1][col+1].rgbtGreen;
				GREEN_pix_y = dy[1][1]*image[row][col].rgbtGreen + dy[1][2]*image[row][col+1].rgbtGreen + dy[0][1]*image[row-1][col].rgbtGreen + dy[0][2]*image[row-1][col+1].rgbtGreen;

				GREEN_pix_x_squared = powf(GREEN_pix_x, 2.0);
				GREEN_pix_y_squared = powf(GREEN_pix_y, 2.0);

				val_temp = (int) round(sqrt(GREEN_pix_x_squared + GREEN_pix_y_squared));

				if (val_temp >= 255)
				{
					temp[row][col].rgbtGreen = 255;
				}
				else
				{
					temp[row][col].rgbtGreen = (int) round(sqrt(GREEN_pix_x_squared + GREEN_pix_y_squared));
				}

				// BLUE
				BLUE_pix_x = dx[1][1]*image[row][col].rgbtBlue + dx[1][2]*image[row][col+1].rgbtBlue + dx[0][1]*image[row-1][col].rgbtBlue + dx[0][2]*image[row-1][col+1].rgbtBlue;
				BLUE_pix_y = dy[1][1]*image[row][col].rgbtBlue + dy[1][2]*image[row][col+1].rgbtBlue + dy[0][1]*image[row-1][col].rgbtBlue + dy[0][2]*image[row-1][col+1].rgbtBlue;

				BLUE_pix_x_squared = powf(BLUE_pix_x, 2.0);
				BLUE_pix_y_squared = powf(BLUE_pix_y, 2.0);

				val_temp = (int) round(sqrt(BLUE_pix_x_squared + BLUE_pix_y_squared));

				if (val_temp >= 255)
				{
					temp[row][col].rgbtBlue = 255;
				}
				else
				{
					temp[row][col].rgbtBlue = (int) round(sqrt(BLUE_pix_x_squared + BLUE_pix_y_squared));
				}


			}

			if ((row == height-1) && (col == width-1))
			{
				// RED
				RED_pix_x = dx[1][1]*image[row][col].rgbtRed + dx[0][1]*image[row-1][col].rgbtRed + dx[1][0]*image[row][col-1].rgbtRed + dx[0][0]*image[row-1][col-1].rgbtRed;
				RED_pix_y = dy[1][1]*image[row][col].rgbtRed + dy[0][1]*image[row-1][col].rgbtRed + dy[1][0]*image[row][col-1].rgbtRed + dy[0][0]*image[row-1][col-1].rgbtRed;

				RED_pix_x_squared = powf(RED_pix_x, 2.0);
				RED_pix_y_squared = powf(RED_pix_y, 2.0);

				val_temp = (int) round(sqrt(RED_pix_x_squared + RED_pix_y_squared));

				if (val_temp >= 255)
				{
					temp[row][col].rgbtRed = 255;
				}
				else
				{
					temp[row][col].rgbtRed = (int) round(sqrt(RED_pix_x_squared + RED_pix_y_squared));
				}


				// GREEN
				GREEN_pix_x = dx[1][1]*image[row][col].rgbtGreen + dx[0][1]*image[row-1][col].rgbtGreen + dx[1][0]*image[row][col-1].rgbtGreen + dx[0][0]*image[row-1][col-1].rgbtGreen;
				GREEN_pix_y = dy[1][1]*image[row][col].rgbtGreen + dy[0][1]*image[row-1][col].rgbtGreen + dy[1][0]*image[row][col-1].rgbtGreen + dy[0][0]*image[row-1][col-1].rgbtGreen;

				GREEN_pix_x_squared = powf(GREEN_pix_x, 2.0);
				GREEN_pix_y_squared = powf(GREEN_pix_y, 2.0);

				val_temp = (int) round(sqrt(GREEN_pix_x_squared + GREEN_pix_y_squared));

				if (val_temp >= 255)
				{
					temp[row][col].rgbtGreen = 255;
				}
				else
				{
					temp[row][col].rgbtGreen = (int) round(sqrt(GREEN_pix_x_squared + GREEN_pix_y_squared));
				}

				// BLUE
				BLUE_pix_x = dx[1][1]*image[row][col].rgbtBlue + dx[0][1]*image[row-1][col].rgbtBlue + dx[1][0]*image[row][col-1].rgbtBlue + dx[0][0]*image[row-1][col-1].rgbtBlue;
				BLUE_pix_y = dy[1][1]*image[row][col].rgbtBlue + dy[0][1]*image[row-1][col].rgbtBlue + dy[1][0]*image[row][col-1].rgbtBlue + dy[0][0]*image[row-1][col-1].rgbtBlue;

				BLUE_pix_x_squared = powf(BLUE_pix_x, 2.0);
				BLUE_pix_y_squared = powf(BLUE_pix_y, 2.0);

				val_temp = (int) round(sqrt(BLUE_pix_x_squared + BLUE_pix_y_squared));

				if (val_temp >= 255)
				{
					temp[row][col].rgbtBlue = 255;
				}
				else
				{
					temp[row][col].rgbtBlue = (int) round(sqrt(BLUE_pix_x_squared + BLUE_pix_y_squared));
				}


			}

			if ((row == 0) && (col != 0) && (col != width-1))
			{
				// RED
				RED_pix_x = dx[1][1]*image[row][col].rgbtRed + dx[1][0]*image[row][col-1].rgbtRed + dx[1][2]*image[row][col+1].rgbtRed + \
							 dx[2][0]*image[row+1][col-1].rgbtRed + dx[2][1]*image[row+1][col].rgbtRed + dx[2][2]*image[row+1][col+1].rgbtRed;

				RED_pix_y = dy[1][1]*image[row][col].rgbtRed + dy[1][0]*image[row][col-1].rgbtRed + dy[1][2]*image[row][col+1].rgbtRed + \
							 dy[2][0]*image[row+1][col-1].rgbtRed + dy[2][1]*image[row+1][col].rgbtRed + dy[2][2]*image[row+1][col+1].rgbtRed;

				RED_pix_x_squared = powf(RED_pix_x, 2.0);
				RED_pix_y_squared = powf(RED_pix_y, 2.0);

				val_temp = (int) round(sqrt(RED_pix_x_squared + RED_pix_y_squared));

				if (val_temp >= 255)
				{
					temp[row][col].rgbtRed = 255;
				}
				else
				{
					temp[row][col].rgbtRed = (int) round(sqrt(RED_pix_x_squared + RED_pix_y_squared));
				}


				// GREEN
				GREEN_pix_x = dx[1][1]*image[row][col].rgbtGreen + dx[1][0]*image[row][col-1].rgbtGreen + dx[1][2]*image[row][col+1].rgbtGreen + \
							 dx[2][0]*image[row+1][col-1].rgbtGreen + dx[2][1]*image[row+1][col].rgbtGreen + dx[2][2]*image[row+1][col+1].rgbtGreen;

				GREEN_pix_y = dy[1][1]*image[row][col].rgbtGreen + dy[1][0]*image[row][col-1].rgbtGreen + dy[1][2]*image[row][col+1].rgbtGreen + \
							 dy[2][0]*image[row+1][col-1].rgbtGreen + dy[2][1]*image[row+1][col].rgbtGreen + dy[2][2]*image[row+1][col+1].rgbtGreen;

				GREEN_pix_x_squared = powf(GREEN_pix_x, 2.0);
				GREEN_pix_y_squared = powf(GREEN_pix_y, 2.0);

				val_temp = (int) round(sqrt(GREEN_pix_x_squared + GREEN_pix_y_squared));

				if (val_temp >= 255)
				{
					temp[row][col].rgbtGreen = 255;
				}
				else
				{
					temp[row][col].rgbtGreen = (int) round(sqrt(GREEN_pix_x_squared + GREEN_pix_y_squared));
				}


				// BLUE
				BLUE_pix_x = dx[1][1]*image[row][col].rgbtBlue + dx[1][0]*image[row][col-1].rgbtBlue + dx[1][2]*image[row][col+1].rgbtBlue + \
							 dx[2][0]*image[row+1][col-1].rgbtBlue + dx[2][1]*image[row+1][col].rgbtBlue + dx[2][2]*image[row+1][col+1].rgbtBlue;

				BLUE_pix_y = dy[1][1]*image[row][col].rgbtBlue + dy[1][0]*image[row][col-1].rgbtBlue + dy[1][2]*image[row][col+1].rgbtBlue + \
							 dy[2][0]*image[row+1][col-1].rgbtBlue + dy[2][1]*image[row+1][col].rgbtBlue + dy[2][2]*image[row+1][col+1].rgbtBlue;

				BLUE_pix_x_squared = powf(BLUE_pix_x, 2.0);
				BLUE_pix_y_squared = powf(BLUE_pix_y, 2.0);

				val_temp = (int) round(sqrt(BLUE_pix_x_squared + BLUE_pix_y_squared));

				if (val_temp >= 255)
				{
					temp[row][col].rgbtBlue = 255;
				}
				else
				{
					temp[row][col].rgbtBlue = (int) round(sqrt(BLUE_pix_x_squared + BLUE_pix_y_squared));
				}


			}

			if ((row != 0) && (row != height-1) && (col == 0))
			{
				// RED
				RED_pix_x = dx[1][1]*image[row][col].rgbtRed + dx[0][1]*image[row-1][col].rgbtRed + dx[2][1]*image[row+1][col].rgbtRed + \
							dx[0][2]*image[row-1][col+1].rgbtRed + dx[1][2]*image[row][col+1].rgbtRed + dx[2][2]*image[row+1][col+1].rgbtRed;

				RED_pix_y = dy[1][1]*image[row][col].rgbtRed + dy[0][1]*image[row-1][col].rgbtRed + dy[2][1]*image[row+1][col].rgbtRed + \
							dy[0][2]*image[row-1][col+1].rgbtRed + dy[1][2]*image[row][col+1].rgbtRed + dy[2][2]*image[row+1][col+1].rgbtRed;

				RED_pix_x_squared = powf(RED_pix_x, 2.0);
				RED_pix_y_squared = powf(RED_pix_y, 2.0);

				val_temp = (int) round(sqrt(RED_pix_x_squared + RED_pix_y_squared));

				if (val_temp >= 255)
				{
					temp[row][col].rgbtRed = 255;
				}
				else
				{
					temp[row][col].rgbtRed = (int) round(sqrt(RED_pix_x_squared + RED_pix_y_squared));
				}


				// GREEN
				GREEN_pix_x = dx[1][1]*image[row][col].rgbtGreen + dx[0][1]*image[row-1][col].rgbtGreen + dx[2][1]*image[row+1][col].rgbtGreen + \
							dx[0][2]*image[row-1][col+1].rgbtGreen + dx[1][2]*image[row][col+1].rgbtGreen + dx[2][2]*image[row+1][col+1].rgbtGreen;

				GREEN_pix_y = dy[1][1]*image[row][col].rgbtGreen + dy[0][1]*image[row-1][col].rgbtGreen + dy[2][1]*image[row+1][col].rgbtGreen + \
							  dy[0][2]*image[row-1][col+1].rgbtGreen + dy[1][2]*image[row][col+1].rgbtGreen + dy[2][2]*image[row+1][col+1].rgbtGreen;

				GREEN_pix_x_squared = powf(GREEN_pix_x, 2.0);
				GREEN_pix_y_squared = powf(GREEN_pix_y, 2.0);

				val_temp = (int) round(sqrt(GREEN_pix_x_squared + GREEN_pix_y_squared));

				if (val_temp >= 255)
				{
					temp[row][col].rgbtGreen = 255;
				}
				else
				{
					temp[row][col].rgbtGreen = (int) round(sqrt(GREEN_pix_x_squared + GREEN_pix_y_squared));
				}

				// BLUE
				BLUE_pix_x = dx[1][1]*image[row][col].rgbtBlue + dx[0][1]*image[row-1][col].rgbtBlue + dx[2][1]*image[row+1][col].rgbtBlue + \
							dx[0][2]*image[row-1][col+1].rgbtBlue + dx[1][2]*image[row][col+1].rgbtBlue + dx[2][2]*image[row+1][col+1].rgbtBlue;

				BLUE_pix_y = dy[1][1]*image[row][col].rgbtBlue + dy[0][1]*image[row-1][col].rgbtBlue + dy[2][1]*image[row+1][col].rgbtBlue + \
							dy[0][2]*image[row-1][col+1].rgbtBlue + dy[1][2]*image[row][col+1].rgbtBlue + dy[2][2]*image[row+1][col+1].rgbtBlue;

				BLUE_pix_x_squared = powf(BLUE_pix_x, 2.0);
				BLUE_pix_y_squared = powf(BLUE_pix_y, 2.0);

				val_temp = (int) round(sqrt(BLUE_pix_x_squared + BLUE_pix_y_squared));

				if (val_temp >= 255)
				{
					temp[row][col].rgbtBlue = 255;
				}
				else
				{
					temp[row][col].rgbtBlue = (int) round(sqrt(BLUE_pix_x_squared + BLUE_pix_y_squared));
				}



			}

			if ((row == height-1) && (col != 0) && (col != width-1))
			{
				// RED
				RED_pix_x = dx[1][1]*image[row][col].rgbtRed + dx[1][0]*image[row][col-1].rgbtRed + dx[1][2]*image[row][col+1].rgbtRed + \
							dx[0][0]*image[row-1][col-1].rgbtRed + dx[0][1]*image[row-1][col].rgbtRed + dx[0][2]*image[row-1][col+1].rgbtRed;

				RED_pix_y = dy[1][1]*image[row][col].rgbtRed + dy[1][0]*image[row][col-1].rgbtRed + dy[1][2]*image[row][col+1].rgbtRed + \
							dy[0][0]*image[row-1][col-1].rgbtRed + dy[0][1]*image[row-1][col].rgbtRed + dy[0][2]*image[row-1][col+1].rgbtRed;

				RED_pix_x_squared = powf(RED_pix_x, 2.0);
				RED_pix_y_squared = powf(RED_pix_y, 2.0);

				val_temp = (int) round(sqrt(RED_pix_x_squared + RED_pix_y_squared));

				if (val_temp >= 255)
				{
					temp[row][col].rgbtRed = 255;
				}
				else
				{
					temp[row][col].rgbtRed = (int) round(sqrt(RED_pix_x_squared + RED_pix_y_squared));
				}


				// GREEN
				GREEN_pix_x = dx[1][1]*image[row][col].rgbtGreen + dx[1][0]*image[row][col-1].rgbtGreen + dx[1][2]*image[row][col+1].rgbtGreen + \
							dx[0][0]*image[row-1][col-1].rgbtGreen + dx[0][1]*image[row-1][col].rgbtGreen + dx[0][2]*image[row-1][col+1].rgbtGreen;

				GREEN_pix_y = dy[1][1]*image[row][col].rgbtGreen + dy[1][0]*image[row][col-1].rgbtGreen + dy[1][2]*image[row][col+1].rgbtGreen + \
							dy[0][0]*image[row-1][col-1].rgbtGreen + dy[0][1]*image[row-1][col].rgbtGreen + dy[0][2]*image[row-1][col+1].rgbtGreen;

				GREEN_pix_x_squared = powf(GREEN_pix_x, 2.0);
				GREEN_pix_y_squared = powf(GREEN_pix_y, 2.0);

				val_temp = (int) round(sqrt(GREEN_pix_x_squared + GREEN_pix_y_squared));

				if (val_temp >= 255)
				{
					temp[row][col].rgbtGreen = 255;
				}
				else
				{
					temp[row][col].rgbtGreen = (int) round(sqrt(GREEN_pix_x_squared + GREEN_pix_y_squared));
				}

				// BLUE
				BLUE_pix_x = dx[1][1]*image[row][col].rgbtBlue + dx[1][0]*image[row][col-1].rgbtBlue + dx[1][2]*image[row][col+1].rgbtBlue + \
				        	  dx[0][0]*image[row-1][col-1].rgbtBlue + dx[0][1]*image[row-1][col].rgbtBlue + dx[0][2]*image[row-1][col+1].rgbtBlue;

				BLUE_pix_y = dy[1][1]*image[row][col].rgbtBlue + dy[1][0]*image[row][col-1].rgbtBlue + dy[1][2]*image[row][col+1].rgbtBlue + \
							dy[0][0]*image[row-1][col-1].rgbtBlue + dy[0][1]*image[row-1][col].rgbtBlue + dy[0][2]*image[row-1][col+1].rgbtBlue;

				BLUE_pix_x_squared = powf(BLUE_pix_x, 2.0);
				BLUE_pix_y_squared = powf(BLUE_pix_y, 2.0);

				val_temp = (int) round(sqrt(BLUE_pix_x_squared + BLUE_pix_y_squared));

				if (val_temp >= 255)
				{
					temp[row][col].rgbtBlue = 255;
				}
				else
				{
					temp[row][col].rgbtBlue = (int) round(sqrt(BLUE_pix_x_squared + BLUE_pix_y_squared));
				}



			}

			if ((row != 0) && (row != height-1) && (col == width-1))
			{
				// RED
				RED_pix_x = dx[1][1]*image[row][col].rgbtRed + dx[0][1]*image[row-1][col].rgbtRed + dx[2][1]*image[row+1][col].rgbtRed + \
							dx[2][0]*image[row+1][col-1].rgbtRed + dx[1][0]*image[row][col-1].rgbtRed + dx[0][0]*image[row-1][col-1].rgbtRed;

				RED_pix_y = dy[1][1]*image[row][col].rgbtRed + dy[0][1]*image[row-1][col].rgbtRed + dy[2][1]*image[row+1][col].rgbtRed + \
							dy[2][0]*image[row+1][col-1].rgbtRed + dy[1][0]*image[row][col-1].rgbtRed + dy[0][0]*image[row-1][col-1].rgbtRed;

				RED_pix_x_squared = powf(RED_pix_x, 2.0);
				RED_pix_y_squared = powf(RED_pix_y, 2.0);

				val_temp = (int) round(sqrt(RED_pix_x_squared + RED_pix_y_squared));

				if (val_temp >= 255)
				{
					temp[row][col].rgbtRed = 255;
				}
				else
				{
					temp[row][col].rgbtRed = (int) round(sqrt(RED_pix_x_squared + RED_pix_y_squared));
				}


				// GREEN
				GREEN_pix_x = dx[1][1]*image[row][col].rgbtGreen + dx[0][1]*image[row-1][col].rgbtGreen + dx[2][1]*image[row+1][col].rgbtGreen + \
							dx[2][0]*image[row+1][col-1].rgbtGreen + dx[1][0]*image[row][col-1].rgbtGreen + dx[0][0]*image[row-1][col-1].rgbtGreen;

				GREEN_pix_y = dy[1][1]*image[row][col].rgbtGreen + dy[0][1]*image[row-1][col].rgbtGreen + dy[2][1]*image[row+1][col].rgbtGreen + \
							dy[2][0]*image[row+1][col-1].rgbtGreen + dy[1][0]*image[row][col-1].rgbtGreen + dy[0][0]*image[row-1][col-1].rgbtGreen;

				GREEN_pix_x_squared = powf(GREEN_pix_x, 2.0);
				GREEN_pix_y_squared = powf(GREEN_pix_y, 2.0);

				val_temp = (int) round(sqrt(GREEN_pix_x_squared + GREEN_pix_y_squared));

				if (val_temp >= 255)
				{
					temp[row][col].rgbtGreen = 255;
				}
				else
				{
					temp[row][col].rgbtGreen = (int) round(sqrt(GREEN_pix_x_squared + GREEN_pix_y_squared));
				}

				// BLUE
				BLUE_pix_x = dx[1][1]*image[row][col].rgbtBlue + dx[0][1]*image[row-1][col].rgbtBlue + dx[2][1]*image[row+1][col].rgbtBlue + \
							dx[2][0]*image[row+1][col-1].rgbtBlue + dx[1][0]*image[row][col-1].rgbtBlue + dx[0][0]*image[row-1][col-1].rgbtBlue;

				BLUE_pix_y = dy[1][1]*image[row][col].rgbtBlue + dy[0][1]*image[row-1][col].rgbtBlue + dy[2][1]*image[row+1][col].rgbtBlue + \
							dy[2][0]*image[row+1][col-1].rgbtBlue + dy[1][0]*image[row][col-1].rgbtBlue + dy[0][0]*image[row-1][col-1].rgbtBlue;

				BLUE_pix_x_squared = powf(BLUE_pix_x, 2.0);
				BLUE_pix_y_squared = powf(BLUE_pix_y, 2.0);

				val_temp = (int) round(sqrt(BLUE_pix_x_squared + BLUE_pix_y_squared));

				if (val_temp >= 255)
				{
					temp[row][col].rgbtBlue = 255;
				}
				else
				{
					temp[row][col].rgbtBlue = (int) round(sqrt(BLUE_pix_x_squared + BLUE_pix_y_squared));
				}


			}

			if ((row != 0) && (row != height-1) && (col != 0) && (col !=width-1))
			{
				// RED
				RED_pix_x = dx[0][0]*image[row-1][col-1].rgbtRed + dx[0][1]*image[row-1][col].rgbtRed + dx[0][2]*image[row-1][col+1].rgbtRed + \
							dx[1][0]*image[row][col-1].rgbtRed + dx[1][1]*image[row][col].rgbtRed + dx[1][2]*image[row][col+1].rgbtRed + \
							dx[2][0]*image[row+1][col-1].rgbtRed + dx[2][1]*image[row+1][col].rgbtRed + dx[2][2]*image[row+1][col+1].rgbtRed;

				RED_pix_y = dy[0][0]*image[row-1][col-1].rgbtRed + dy[0][1]*image[row-1][col].rgbtRed + dy[0][2]*image[row-1][col+1].rgbtRed + \
							dy[1][0]*image[row][col-1].rgbtRed + dy[1][1]*image[row][col].rgbtRed + dy[1][2]*image[row][col+1].rgbtRed + \
							dy[2][0]*image[row+1][col-1].rgbtRed + dy[2][1]*image[row+1][col].rgbtRed + dy[2][2]*image[row+1][col+1].rgbtRed;

				RED_pix_x_squared = powf(RED_pix_x, 2.0);
				RED_pix_y_squared = powf(RED_pix_y, 2.0);

				val_temp = (int) round(sqrt(RED_pix_x_squared + RED_pix_y_squared));

				if (val_temp >= 255)
				{
					temp[row][col].rgbtRed = 255;
				}
				else
				{
					temp[row][col].rgbtRed = (int) round(sqrt(RED_pix_x_squared + RED_pix_y_squared));
				}


				// GREEN
				GREEN_pix_x = dx[0][0]*image[row-1][col-1].rgbtGreen + dx[0][1]*image[row-1][col].rgbtGreen + dx[0][2]*image[row-1][col+1].rgbtGreen + \
							  dx[1][0]*image[row][col-1].rgbtGreen + dx[1][1]*image[row][col].rgbtGreen + dx[1][2]*image[row][col+1].rgbtGreen + \
						      dx[2][0]*image[row+1][col-1].rgbtGreen + dx[2][1]*image[row+1][col].rgbtGreen + dx[2][2]*image[row+1][col+1].rgbtGreen;

				GREEN_pix_y = dy[0][0]*image[row-1][col-1].rgbtGreen + dy[0][1]*image[row-1][col].rgbtGreen + dy[0][2]*image[row-1][col+1].rgbtGreen + \
							  dy[1][0]*image[row][col-1].rgbtGreen + dy[1][1]*image[row][col].rgbtGreen + dy[1][2]*image[row][col+1].rgbtGreen + \
							  dy[2][0]*image[row+1][col-1].rgbtGreen + dy[2][1]*image[row+1][col].rgbtGreen + dy[2][2]*image[row+1][col+1].rgbtGreen;

				GREEN_pix_x_squared = powf(GREEN_pix_x, 2.0);
				GREEN_pix_y_squared = powf(GREEN_pix_y, 2.0);

				val_temp = (int) round(sqrt(GREEN_pix_x_squared + GREEN_pix_y_squared));

				if (val_temp >= 255)
				{
					temp[row][col].rgbtGreen = 255;
				}
				else
				{
					temp[row][col].rgbtGreen = (int) round(sqrt(GREEN_pix_x_squared + GREEN_pix_y_squared));
				}

				// BLUE
				BLUE_pix_x = dx[0][0]*image[row-1][col-1].rgbtBlue + dx[0][1]*image[row-1][col].rgbtBlue + dx[0][2]*image[row-1][col+1].rgbtBlue + \
							dx[1][0]*image[row][col-1].rgbtBlue + dx[1][1]*image[row][col].rgbtBlue + dx[1][2]*image[row][col+1].rgbtBlue + \
							dx[2][0]*image[row+1][col-1].rgbtBlue + dx[2][1]*image[row+1][col].rgbtBlue + dx[2][2]*image[row+1][col+1].rgbtBlue;

				BLUE_pix_y = dy[0][0]*image[row-1][col-1].rgbtBlue + dy[0][1]*image[row-1][col].rgbtBlue + dy[0][2]*image[row-1][col+1].rgbtBlue + \
							  dy[1][0]*image[row][col-1].rgbtBlue + dy[1][1]*image[row][col].rgbtBlue + dy[1][2]*image[row][col+1].rgbtBlue + \
							  dy[2][0]*image[row+1][col-1].rgbtBlue + dy[2][1]*image[row+1][col].rgbtBlue + dy[2][2]*image[row+1][col+1].rgbtBlue;

				BLUE_pix_x_squared = powf(BLUE_pix_x, 2.0);
				BLUE_pix_y_squared = powf(BLUE_pix_y, 2.0);

				val_temp = (int) round(sqrt(BLUE_pix_x_squared + BLUE_pix_y_squared));

				if (val_temp >= 255)
				{
					temp[row][col].rgbtBlue = 255;
				}
				else
				{
					temp[row][col].rgbtBlue = (int) round(sqrt(BLUE_pix_x_squared + BLUE_pix_y_squared));
				}


			}
		}
	}

	for (int i = 0 ; i < height ; i++)
	{
		for (int j = 0 ; j < width ; j++)
		{
			image[i][j].rgbtRed = temp[i][j].rgbtRed;
			image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
			image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
		}
	}
    return;
}
