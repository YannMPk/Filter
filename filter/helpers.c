#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
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
            int newrgbtRed =   round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int newrgbtGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int newrgbtBlue =  round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            image[i][j].rgbtRed = ((newrgbtRed > 255) ? 255 : newrgbtRed);
            image[i][j].rgbtGreen = ((newrgbtGreen > 255) ? 255 : newrgbtGreen);
            image[i][j].rgbtBlue = ((newrgbtBlue > 255) ? 255 : newrgbtBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];

// exchanging of cell values (swap)
    for (int i = 0; i <= height; i++)
    {
        for (int j = 0, l = width - 1; j < l; j++, l--)
        {
            tmp[i][j]   = image[i][j];
            image[i][j] = image[i][l];
            image[i][l] = tmp[i][j];
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
        for (int j = 0; j < width; j++)
        {
            int counter = 0;

            //case autour du pixel ciblé

            int Gx[] = {i - 1, i, i + 1};
            int Gy[] = {j - 1, j, j + 1};

            // total of rgbtRed, rgbtGreen and rgbtBlue
            float Red = 0, Green = 0, Blue = 0 ;

            //sum of the values of the cells forming a 3x3 array
            for (int row = 0; row < 3; row++)
            {
                for (int col = 0; col < 3; col++)
                {
                    int currentrow = Gx[row];
                    int currentcol = Gy[col];

                    if (currentrow >= 0 && currentrow < height && currentcol >= 0 && currentcol < width)
                    {
                        Red   += image[currentrow][currentcol].rgbtRed;
                        Green += image[currentrow][currentcol].rgbtGreen;
                        Blue  += image[currentrow][currentcol].rgbtBlue;
                        counter++;
                    }
                }
            }

            //averaging
            temp[i][j].rgbtRed   = round(Red / counter);
            temp[i][j].rgbtGreen = round(Green / counter);
            temp[i][j].rgbtBlue = round(Blue / counter);

        }
    }
    //the final image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image [i][j] = temp[i][j];
        }
    }
    return;
}
