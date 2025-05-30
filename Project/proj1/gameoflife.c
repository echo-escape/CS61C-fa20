/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", 
// so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
int tenToBinaryWithIndex(uint8_t number, int index);
uint8_t evaluateOneCellForOneColor(Image *image, int row, int col, int *rule, char identify);

Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	//YOUR CODE HERE
	int length = sizeof(uint32_t) * 8; 
	int ruleConvert[length];
	for (int i = 0; i < length; i++)
	{
		int shifted_number = rule >> i;
		int bit = shifted_number & 1;
		ruleConvert[i] = bit;
	}

	Color *color = (Color *) malloc(sizeof(Color));
	if (color == NULL)
	{
		free(color);
		return NULL;
	}

	uint8_t redNumber = evaluateOneCellForOneColor(image, row, col, ruleConvert, 'R');
	uint8_t greenNumber = evaluateOneCellForOneColor(image, row, col, ruleConvert, 'G');
	uint8_t blueNumber = evaluateOneCellForOneColor(image, row, col, ruleConvert, 'B');

	color->R = redNumber;
	color->G = greenNumber;
	color->B = blueNumber;

	return color;
}

uint8_t evaluateOneCellForOneColor(Image *image, int row, int col, int *rule, char identify)
{
	int width = image->cols;
	int height = image->rows;
	int colorNumber = 0;

	if (identify == 'R')
	{
		colorNumber = image->image[row][col].R;
	}
	else if (identify == 'G')
	{
		colorNumber = image->image[row][col].G;
	}
	else
	{
		colorNumber = image->image[row][col].B;
	}
	
	uint8_t binaryNumber[sizeof(uint8_t) * 8];
	int numBits = sizeof(uint8_t) * 8;
	for (int i = numBits - 1; i >= 0; i--)
	{
		uint8_t shifted_number = colorNumber >> i;
		uint8_t digit = shifted_number & 1;
		binaryNumber[7 - i] = digit;
	}

	int length = numBits;
	for (int i = 0; i < length; i++)
	{
		int xOff[3] = {-1, 0, 1};
		int yOff[3] = {-1, 0, 1};
		int count = 0;
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				int xOffSet = row + xOff[j];
				int yOffSet = col + yOff[k];
				if (xOffSet < 0 || xOffSet > height - 1 || (xOffSet == row && yOffSet == col)) 
				{
					continue;
				}
				if (yOffSet < 0 || yOffSet > width - 1)
				{
					continue;
				}
				Color tempColor = image->image[xOffSet][yOffSet];
				int temp = 0;
				if (identify == 'R')
				{
					temp = tempColor.R;
				}
				else if (identify == 'G')
				{
					temp = tempColor.G;
				}
				else
				{
					temp = tempColor.B;
				}
				int tempBinary = tenToBinaryWithIndex(temp, i);
				if (tempBinary == 1)
				{
					count++;
				}
			}
		}
		int changeDigit = 0;
		if (binaryNumber[i] == 1)
		{
			if (count == 2 || count == 3)
			{
				changeDigit = 1;
			}
		}
		else
		{
			if (count == 3)
			{
				changeDigit = 1;
			}
		}
		binaryNumber[i] = changeDigit;
	}

	uint8_t result = 0;
	for (int i = 0; i < length; i++)
	{
		result = result << 1;
		result = result | binaryNumber[i]; 
	}
	return result;
}

int tenToBinaryWithIndex(uint8_t number, int index)
{
	int numBits = sizeof(uint8_t) * 8;
	return (number >> (numBits - 1 - index)) & 1;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	//YOUR CODE HERE
	int width = image->cols;
	int height = image->rows;

	Image *newImage = (Image *) malloc(sizeof(Image));
	if (newImage == NULL)
	{
		free(newImage);
		return NULL;
	}
	newImage->rows = height;
	newImage->cols = width;
	newImage->image = (Color **) malloc(sizeof(Color *) * height);
	if (newImage->image == NULL)
	{
		free(newImage->image);
		return NULL;
	}
	for (int i = 0; i < height; i++)
	{
		newImage->image[i] = (Color *) malloc(sizeof(Color) * width);
		if (newImage->image[i] == NULL)
		{
			free(newImage->image[i]);
			return NULL;
		}
		for (int j = 0; j < width; j++)
		{
			Color *color = NULL;
			color = evaluateOneCell(image, i, j, rule);
			if (color == NULL) {
				fprintf(stderr, "Error: evaluateOneCell returned NULL for cell (%d, %d).\n", i, j);
				for (int k_free = 0; k_free <= i; k_free++) {
					free(newImage->image[k_free]); 
				}
				free(newImage->image);
				free(newImage);
				return NULL; 
			}
			newImage->image[i][j].R = color->R;
			newImage->image[i][j].G = color->G;
			newImage->image[i][j].B = color->B;
			free(color);
		}
	}
	return newImage;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	if (argc != 3)
	{
		printf("filename is an ASCII PPM file (type P3) with maximum value 255.\n");
		printf("rule is a hex number beginning with 0x; Life is 0x1808.");
		return -1;
	}
	
	char *filename = argv[1];
	char *ruleString = argv[2];
	if (ruleString == NULL)
	{
		return -1;
	}

	char *endptr = NULL;
	uint32_t rule = strtoul(ruleString, &endptr, 16);

	Image *image = NULL;
	Image *newImage = NULL;
	image = readData(filename);
	if (image == NULL)
	{
		return -1;
	}
	newImage = life(image, rule);
	if (newImage == NULL) { // 确保检查 life 的返回值
		fprintf(stderr, "Error: life function returned NULL.\n");
		freeImage(image); // 仍然需要释放原始图像
		return -1;
	}
	writeData(newImage);
	freeImage(image);
	freeImage(newImage);
	return 0;
}
