#include <stdio.h>
#include "simplecomplex.h"

#ifndef CALCULATIONS
#define CALCULATIONS

extern size_t calculate_fractal(complex * c, size_t limit);
extern complex pixel_to_point(size_t width, size_t height, size_t pixel_x, size_t pixel_y, complex upper_left, complex lower_right);
extern unsigned char * render(size_t width, size_t height, complex upper_left, complex lower_right, size_t limit);

#endif //CALCULATIONS