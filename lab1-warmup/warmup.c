/*
Author: David J. Bourke - 12304135
Date:   30th - September - 2016
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef unsigned char shade;

void draw_mandlebrot(int, int, int, shade*);
void write_image(shade*, int, int, char*);

int main (void) {
	// Higher values will lead to a better fractal
	unsigned int width = 1024;//26500
	unsigned int height = 1024;//26500
	// Here we define a datatype to represent the value of a single colour
	// channel of a single pixel
	shade default_shade = 255;
	shade dark = 0;
	shade alt = 128;

	shade* image_data = (shade*)malloc(width * height * 3 * sizeof(shade));
	// Initialise each element of the array to default_shade value
	for (int x = 0; x < width * height * 3; x++) {
		memcpy(image_data + x * sizeof(shade), &default_shade, sizeof(shade));
	}
	// Draw a diagonal line
	for (int y = 0; y < height - 9; y++) {
		for (int x = y; x < y + 9; x++) {
			memcpy(image_data + y * width * 3 + x * 3 + 0, &dark, sizeof(shade));
			memcpy(image_data + y * width * 3 + x * 3 + 1, &dark, sizeof(shade));
			memcpy(image_data + y * width * 3 + x * 3 + 2, &alt, sizeof(shade));
		}
	}

	// Write the diagonal line to a file
	printf("Writing image to file line.ppm...\n");
	write_image(image_data, width, height, "line.ppm");

	// Calculate mandelbrot set, store result in image_data and write to file
	draw_mandlebrot(width, height, 255, image_data);
	printf("Writing image to file mandelbrot.ppm...\n");
	write_image(image_data, width, height, "mandlebrot.ppm");

	free(image_data);
	image_data = NULL;
	
    return 0;
}

void write_image(shade* image_data, int width, int height, char* filename) {
	FILE *p_image = fopen(filename, "w");
	/* ppm header in the format: 
	P3
	width (in pixels), height (in pixels)
	colour depth */
	fprintf(p_image, "P3\n#%s\n%u %u\n%u\n", filename, width, height, 255);
	// Write image_data to file
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			fprintf(p_image, "%i %i %i\t",
				image_data[y * width * 3 + x * 3 + 0],
				image_data[y * width * 3 + x * 3 + 1],
				image_data[y * width * 3 + x * 3 + 2]
			);
		}
		fprintf(p_image, "\n");
	}
	fclose(p_image);
}

void draw_mandlebrot(int width, int height, int fractal_dimension, shade* dest_image) {
	double c_real, c_imag, z_real, z_imag, swap;
	shade r, g, b;
	int i;	// Used as to count iterations mandlebrot function
	for (int row = 0, r = 0, g = 0, b = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			c_real = (col - width / (double)2) * (double)4 / width;
			c_imag = (row - height / (double)2) * (double)4 / height;
			z_real = 0;
			z_imag = 0;
			for (i = 0; (z_imag * z_imag + c_imag * c_imag <= 4) && (i < fractal_dimension); i++) {
				swap = z_real * z_real - z_imag * z_imag + c_real;
				z_imag = 2 * z_real * z_imag + c_imag;
				z_real = swap;
			}
			if (i < fractal_dimension) {
				// These colours are picked arbitrarily
				r = 50;
				g = i;
				b = 50;
			} else {
				r = 0;
				g = 0;
				b = 0;
			}
			memcpy(dest_image + width * row * 3 + col * 3 + 0, &r, sizeof(shade));
			memcpy(dest_image + width * row * 3 + col * 3 + 1, &g, sizeof(shade));
			memcpy(dest_image + width * row * 3 + col * 3 + 2, &b, sizeof(shade));
		}
	}
}