#include "helpers.h"
#include  <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;
            avg = round((red + green + blue) / 3);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen =  avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float red   = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;
            int sepiared = round(.393 * red + .769 * green + .189 * blue);
            int sepiagreen =  round(.349 * red + .686 * green + .168 * blue);
            int sepiablue = round(.272 * red + .534 * green + .131 * blue);
            if (sepiared > 255)
            {
                sepiared = 255;
            }
            if (sepiagreen > 255)
            {
                sepiagreen = 255;
            }
            if (sepiablue > 255)
            {
                sepiablue = 255;
            }
            image[i][j].rgbtRed = sepiared;
            image[i][j].rgbtGreen = sepiagreen;
            image[i][j].rgbtBlue = sepiablue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, k = width - 1 ; j < width / 2; j++, k--)
        {
            temp[i][j] = image[i][j];
            image[i][j] = image[i][k];
            image[i][k] = temp[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0 ; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0 ; j < width; j++)
        {
            float red, green, blue, n;
            red = green = blue = n = 0;
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    int presentK = i + k ;
                    int  presentL = j + l;
                    if (presentK < 0 || presentK > height - 1 || presentL < 0 || presentL > width - 1)
                    {
                        continue;
                    }
                    red = red + image[presentK][presentL].rgbtRed;
                    green = green + image[presentK][presentL].rgbtGreen;
                    blue = blue + image[presentK][presentL].rgbtBlue;

                    n++;
                }
            }
            temp[i][j].rgbtRed = round(red / n);
            temp[i][j].rgbtGreen = round(green / n);
            temp[i][j].rgbtBlue = round(blue / n);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0 ; j < width; j++)
        {
            image[i][j].rgbtRed =  temp[i][j].rgbtRed ;
            image[i][j].rgbtGreen =   temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue =   temp[i][j].rgbtBlue;
        }
    }
    return;
}
