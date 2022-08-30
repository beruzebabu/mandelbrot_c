#include <stdlib.h>
#include <stdio.h>
#include "simplecomplex.h"

extern size_t calculate_fractal(complex * c, size_t limit) {
    complex z = { 0.0, 0.0 };

    for (size_t i = 0; i < limit; i++)
    {
        if (((z.real * z.real) + (z.imaginary * z.imaginary)) > 4.0)
        {
            if (i > 255) i = 255;
            return 255 - i;
        }
        
        double real = z.real;
        double imag = z.imaginary;

        z.real = (real * real)-(imag * imag);
        z.imaginary = (real * imag)+(real * imag);
        z.real += c->real;
        z.imaginary += c->imaginary;
    }

    return 0;
}

extern void pixel_to_point(complex * point, size_t width, size_t height, size_t pixel_x, size_t pixel_y, complex * upper_left, complex * lower_right) {
    double w = lower_right->real - upper_left->real;
    double h = upper_left->imaginary - lower_right->imaginary;
    
    point->real = upper_left->real + (double)pixel_x * w / (double)width;
    point->imaginary = upper_left->imaginary - (double)pixel_y * h / (double)height;

    return;
}

extern unsigned char * render(size_t width, size_t height, complex upper_left, complex lower_right, size_t limit) {
    unsigned char * image = (unsigned char *)malloc(sizeof(unsigned char) * (width * height));

    if (image == NULL)
    {
        puts("Failed to allocate image buffer\n");
        return NULL;
    }

    complex * point = (complex *)malloc(sizeof(complex));
    if (point == NULL)
    {
        puts("Failed to allocate memory for point calculation\n");
        return NULL;
    }

    for (size_t h = 0; h < height; h++)
    {
        for (size_t w = 0; w < width; w++)
        {
            pixel_to_point(point, width, height, w, h, &upper_left, &lower_right);

            if (point == NULL)
            {
                printf_s("Failed to calculate pixel for point: %i, %i\n", w, h);
                return NULL;
            }

            image[w*width+h] = calculate_fractal(point, limit);
        }
    }
    
    free(point);

    return image;
}