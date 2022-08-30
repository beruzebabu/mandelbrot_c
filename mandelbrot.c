#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "calculations.h"
#include "simplecomplex.h"

#include "tinytiff/tinytiffwriter.h"

int main(int argc, char* args[])
{
    if (argc < 9)
    {
        printf_s("Incorrect amount of parameters supplied, exiting!");
        return 1;
    }

    clock_t start_time = clock();

    const char * filename = args[1];

    size_t width = strtoull(args[2], NULL, 10);
    size_t height = strtoull(args[3], NULL, 10);

    if (width == 0ULL || width == ULLONG_MAX)
    {
        printf_s("Could not parse width, exiting!");
        return 1;
    }
    
    if (height == 0ULL || height == ULLONG_MAX)
    {
        printf_s("Could not parse height, exiting!");
        return 1;
    }

    double lu_r = strtod(args[4], NULL);
    double lu_i = strtod(args[5], NULL);
    if ((lu_r == 0.0 || lu_r == HUGE_VAL) || (lu_i == 0.0 || lu_i == HUGE_VAL))
    {
        printf_s("Could not parse left upper complex number, exiting!");
        return 1;
    }
    complex left_upper = { lu_r, lu_i };

    double rl_r = strtod(args[6], NULL);
    double rl_i = strtod(args[7], NULL);
    if ((rl_r == 0.0 || rl_r == HUGE_VAL) || (rl_i == 0.0 || rl_i == HUGE_VAL))
    {
        printf_s("Could not parse right lower complex number, exiting!");
        return 1;
    }
    complex right_lower = { rl_r, rl_i };

    size_t limit = strtoull(args[8], NULL, 10);
    if (limit == 0ULL || limit == ULLONG_MAX)
    {
        printf_s("Could not parse limit, exiting!");
        return 1;
    }

    unsigned char * image = render(width, height, left_upper, right_lower, limit);

    TinyTIFFWriterFile* tif=TinyTIFFWriter_open(filename, 8, TINYTIFF_SAMPLEFORMAT_UINT, 1, width, height, TinyTIFFWriter_Greyscale);
    if (tif) {
        TinyTIFFWriter_writeImage(tif, image);
        TinyTIFFWriter_close(tif);
    }

    free(image);

    clock_t end_time = clock();

    printf_s("Time taken: %fs", (double)(end_time - start_time)/CLOCKS_PER_SEC);
    printf_s("Image written to file %s", filename);

    return 0;
}