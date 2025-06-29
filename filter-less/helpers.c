#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    /*
        - Loop over all the pixels
        - Take average of RGB
        - Update old pixel values
    */

    int new_greyscale_value = 0;
    for(int h = 0; h < height ;h++)
    {
        for(int w = 0; w < width  ;w++)
        {
            new_greyscale_value = (int) round((image[h][w].rgbtRed + image[h][w].rgbtGreen + image[h][w].rgbtBlue)/3.0);
            image[h][w].rgbtRed = image[h][w].rgbtGreen = image[h][w].rgbtBlue = new_greyscale_value;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepia_red, sepia_green, sepia_blue;
    for(int h = 0; h < height ;h++)
    {
        for(int w = 0; w < width  ;w++)
        {
            sepia_red = round(.393 * image[h][w].rgbtRed + .769 * image[h][w].rgbtGreen + .189 * image[h][w].rgbtBlue);
            sepia_green = round(.349 * image[h][w].rgbtRed + .686 * image[h][w].rgbtGreen + .168 * image[h][w].rgbtBlue);
            sepia_blue = round(.272 * image[h][w].rgbtRed + .534 * image[h][w].rgbtGreen + .131 * image[h][w].rgbtBlue);

            // Checking Red Pixel Cap
            if(sepia_red > 255)
            {
                sepia_red = 255;
                image[h][w].rgbtRed = sepia_red;
            }
            else if(sepia_red < 0)
            {
                sepia_red = 0;
                image[h][w].rgbtRed = sepia_red;
            }
            else
            {
                image[h][w].rgbtRed = sepia_red;
            }

            // Checking Green Pixel Cap
            if(sepia_green > 255)
            {
                sepia_green = 255;
                image[h][w].rgbtGreen = sepia_green;
            }
            else if(sepia_green < 0)
            {
                sepia_green = 0;
                image[h][w].rgbtGreen = sepia_green;
            }
            else
            {
                image[h][w].rgbtGreen = sepia_green;
            }

            // Checking Blue Pixel Cap
            if(sepia_blue > 255)
            {
                sepia_blue = 255;
                image[h][w].rgbtBlue = sepia_blue;
            }
            else if(sepia_blue < 0)
            {
                sepia_blue = 0;
                image[h][w].rgbtBlue = sepia_blue;
            }
            else
            {
                image[h][w].rgbtBlue = sepia_blue;
            }
        }
    }

    return;
}


void swap(RGBTRIPLE *a, RGBTRIPLE *b)
{
    RGBTRIPLE temp = *a;
    *a = *b;
    *b = temp;
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    int m = round(width/2);
    for(int h = 0; h < height; h++)
    {
        int row = width - 1;
        for(int w = 0; w < m ; w++)
        {
            swap(&image[h][w], &image[h][row]);
            row--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for(int h = 0; h < height; h++)
    {
        for(int w = 0; w < width; w++)
        {
            copy[h][w] = image[h][w];

        }
    }





    for(int h = 0; h < height; h++)
    {
        for(int w = 0; w < width; w++)
        {
            int count = 0;
            int sum_red = 0;
            int sum_green = 0;
            int sum_blue = 0;
            int avg_red = 0 , avg_green = 0, avg_blue = 0;

            for(int i_h = h - 1; i_h <= h + 1; i_h++)
            {
                for(int i_w = w - 1; i_w <= w + 1; i_w++)
                {
                    if (i_h >= 0 && i_h < height && i_w >= 0 && i_w < width)
                    {
                        sum_red += copy[i_h][i_w].rgbtRed;
                        sum_green += copy[i_h][i_w].rgbtGreen;
                        sum_blue += copy[i_h][i_w].rgbtBlue;
                        count++;
                    }
                }
            }

            avg_red = round((float)sum_red / count);
            avg_green = round((float)sum_green / count);
            avg_blue = round((float)sum_blue / count);

            image[h][w].rgbtRed = avg_red;
            image[h][w].rgbtGreen = avg_green;
            image[h][w].rgbtBlue = avg_blue;
        }
    }


    return;
}
