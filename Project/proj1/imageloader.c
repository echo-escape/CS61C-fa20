/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	//YOUR CODE HERE
	Image *image = (Image *) malloc(sizeof(Image));

	FILE *inputFile = NULL;
	inputFile = fopen(filename, "r");

	char magicNumber[3] = {0};
	fscanf(inputFile, "%2s", magicNumber);
	magicNumber[2] = '\0';

	int width = 0, height = 0;
	fscanf(inputFile, "%d %d", &width, &height);
	image->rows = width;
	image->cols = height;

	int maxColorValue = 0;
	fscanf(inputFile, "%d", &maxColorValue);
	
	image->image = (Color **) malloc(height * sizeof(Color *));
	for (int i = 0; i < height; i++) 
	{
		image->image[i] = (Color *) malloc(width * sizeof(Color));
		for (int j = 0; j < width; j++)
		{
			fscanf(inputFile, "%hhu %hhu %hhu", &image->image[i][j].R, &image->image[i][j].G, &image->image[i][j].B);
		}
	}

	fclose(inputFile);
	return image;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
	int width = image->rows, height = image->cols;
	int maxColorValue = 255;
	char magicNumber[3] = {"P3\0"};
	printf("%s\n", magicNumber);
	printf("%d %d\n", width, height);
	printf("%d\n", maxColorValue);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			printf("%3d %3d %3d", image->image[i][j].R, image->image[i][j].G, image->image[i][j].B);
			if (j != width - 1) 
			{
				printf("   ");
			}
		}
		printf("\n");
	}
}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
	int height = image->cols;
	for (int i = 0; i < height; i++)
	{
		free(image->image[i]);
	}
	free(image->image);
	free(image);
}