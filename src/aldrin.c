#ifndef ALDRIN_H_
#define ALDRIN_H_

#ifndef PLATFORM_WASM
#ifndef PLATFORM_C
#define PLATFORM_C
#endif // PLATFORM_C
#endif // PLATFORM_WASM

#ifdef PLATFORM_C
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#endif // PLATFORM_C

#include <stdint.h>

#define min(a,b) ((int)(a)<(int)(b)?(a):(b))
#define max(a,b) ((int)(a)>(int)(b)?(a):(b))

typedef struct Aldrin_Canvas {
    uint32_t *pixels;
    uint32_t width;
    uint32_t height;
} Aldrin_Canvas;


void aldrin_swap(uint32_t *x1, uint32_t *y1, uint32_t *x2, uint32_t *y2) {
    // swap x
    uint32_t temp = *x1;
    *x1 = *x2;
    *x2 = temp;

    // swap y
    temp = *y1;
    *y1 = *y2;
    *y2 = temp;
}


void aldrin_put_pixel(Aldrin_Canvas ac, uint32_t x, uint32_t y, uint32_t color) {
    ac.pixels[(y*ac.width) + x] = color;
}


void aldrin_fill(Aldrin_Canvas ac, uint32_t fill_color) {
    for (uint32_t p = 0; p < ac.width * ac.height; ++p) {
        ac.pixels[p] = fill_color;
    }
}


void aldrin_calculate_line_formula(uint32_t x1, uint32_t y1, int dx, int dy, double *m, double *c) {
    *m = ((double) dy) / dx;
    *c = y1 - (*m)*x1;
}


// TODO: add smooth curves to top and bottom of line if thickness is greater than 1
void aldrin_draw_line(Aldrin_Canvas ac,
    uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t line_color, uint32_t thickness) {
    
    const int dx = x1-x2;
    const int dy = y1-y2;
    double m, c;
    aldrin_calculate_line_formula(x1, y1, dx, dy, &m, &c);

    if (abs(dx) > abs(dy)) {
        // it is horizontal-ish
        // f(x) = y = mx + c

        for (uint32_t x = min(x1, x2); x <= max(x1, x2); ++x) {
            int y = m*x + c, yt;

            if (y >= (int) min(y1, y2) && y <= (int) max(y1, y2)) {
                aldrin_put_pixel(ac, x, y, line_color);
            }

            for (int i = 1; i < (int) thickness; ++i) {
                yt = (fmod((double) i/2, 1) == 0) ? y-i+i/2 : y+i-i/2;
                if (yt >= 0 && yt < (int) ac.height) {
                    aldrin_put_pixel(ac, x, yt, line_color);
                }
            }
        }

    } else {
        // it is vertical-ish
        // f(y) = x = (y - c) / m

        for (uint32_t y = min(y1, y2); y <= max(y1, y2); ++y) {
            int x, xt;
            x = dx == 0 ? x1 : (y - c) / m;

            if (x >= (int) min(x1, x2) && x <= (int) max(x1, x2)) {
                aldrin_put_pixel(ac, x, y, line_color);
            }

            for (int i = 1; i < (int) thickness; ++i) {
                xt = (fmod((double) i/2, 1) == 0) ? x-i+i/2 : x+i-i/2;

                if (xt >= 0 && xt < (int) ac.width) {
                    aldrin_put_pixel(ac, xt, y, line_color);
                }
            }
        }
    }

}


void aldrin_draw_triangle(Aldrin_Canvas ac,
    uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t x3, uint32_t y3,
    uint32_t line_color, uint32_t thickness) {

    aldrin_draw_line(ac, x1, y1, x2, y2, line_color, thickness);
    aldrin_draw_line(ac, x1, y1, x3, y3, line_color, thickness);
    aldrin_draw_line(ac, x2, y2, x3, y3, line_color, thickness);
}


void aldrin_fill_triangle(Aldrin_Canvas ac,
    uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t x3, uint32_t y3,
    uint32_t fill_color) {

    // scanline triangle fill algorithm

    // make sure y3 > y2 > y1
    if (y1 > y2) {
        aldrin_swap(&x1, &y1, &x2, &y2);
    }

    if (y2 > y3) {
        aldrin_swap(&x2, &y2, &x3, &y3);
    }

    if (y1 > y2) {
        aldrin_swap(&x1, &y1, &x2, &y2);
    }

    // calculate line formula of each line
    const uint32_t dx12 = x1-x2;
    const uint32_t dx13 = x1-x3;
    const uint32_t dx23 = x2-x3;

    const uint32_t dy12 = y1-y2;
    const uint32_t dy13 = y1-y3;
    const uint32_t dy23 = y2-y3;

    double m12, m13, m23, c12, c13, c23;

    aldrin_calculate_line_formula(x1, y1, dx12, dy12, &m12, &c12);
    aldrin_calculate_line_formula(x1, y1, dx13, dy13, &m13, &c13);
    aldrin_calculate_line_formula(x2, y2, dx23, dy23, &m23, &c23);

    // scan and fill first half
    for (uint32_t y = y1; y <= y2; ++y) {

        // f(y) = x = (y - c) / m
        const uint32_t x_start = (m12 == 0 || dx12 == 0) ? x1 : (y - c12) / m12;
        const uint32_t x_end = dx13 == 0 ? x1 : (y - c13) / m13;
        aldrin_draw_line(ac, x_start, y, x_end, y, fill_color, 1);
    }

    // scan and fill second half
    for (uint32_t y = y2; y <= y3; ++y) {

        // f(y) = x = (y - c) / m
        const uint32_t x_start = (m23 == 0 || dx23 == 0) ? x2 : (y - c23) / m23;
        const uint32_t x_end = dx13 == 0 ? x1 : (y - c13) / m13;
        aldrin_draw_line(ac, x_start, y, x_end, y, fill_color, 1);
    }

}


// TODO: add thickness option
// TODO: try to optimize circle functions with better algorithms
void aldrin_draw_circle(Aldrin_Canvas ac, uint32_t x, uint32_t y, uint32_t r,
    uint32_t line_color) {

    // fuck the mid-point circle drawing algorithm
    // using my own fucking best algorithm

    // calculate bounding box
    const uint32_t x_min = max(x-r, 0);
    const uint32_t y_min = max(y-r, 0);
    const uint32_t x_max = min(x+r, ac.width-1);
    const uint32_t y_max = min(y+r, ac.height-1);

    for (int py = y_min; py <= (int) y_max; ++py) {
        for (int px = x_min; px <= (int) x_max; ++px) {
            // calculate distance from point to center of circle
            uint32_t d = sqrt(pow(max(py, y)-min(py, y), 2) + pow(max(px, x)-min(px, x), 2));
            if (d == r) { // just draw outline if equal
                aldrin_put_pixel(ac, px, py, line_color);
            }
        }
    }
}


void aldrin_fill_circle(Aldrin_Canvas ac, uint32_t x, uint32_t y, uint32_t r,
    uint32_t fill_color) {

    // basicly same fucking algorithm of draw_circle

    // calculate bounding box
    const uint32_t x_min = max(x-r, 0);
    const uint32_t y_min = max(y-r, 0);
    const uint32_t x_max = min(x+r, ac.width-1);
    const uint32_t y_max = min(y+r, ac.height-1);

    for (int py = y_min; py <= (int) y_max; ++py) {
        for (int px = x_min; px <= (int) x_max; ++px) {
            // calculate distance from point to center of circle
            uint32_t d = sqrt(pow(max(py, y)-min(py, y), 2) + pow(max(px, x)-min(px, x), 2));
            if (d <= r) { // fill if less than or equal
                aldrin_put_pixel(ac, px, py, fill_color);
            }
        }
    }
}


// makes sense with wasm
uint32_t *aldrin_get_pixels(Aldrin_Canvas ac) {
    return ac.pixels;
}


uint32_t aldrin_get_width(Aldrin_Canvas ac) {
    return ac.width;
}


uint32_t aldrin_get_height(Aldrin_Canvas ac) {
    return ac.height;
}


#ifdef PLATFORM_C

int aldrin_save_ppm(Aldrin_Canvas ac, const char *filename) {
    FILE *f = fopen(filename, "wb");
    if (f == NULL) {
        printf("Cannot open output file %s.\n", filename);
        return 1;
    }

    fprintf(f, "P3\n%d %d 255\n", ac.width, ac.height);

    for (uint32_t p = 0; p < ac.width * ac.height; ++p) {
        const uint8_t r = (ac.pixels[p] >> 16) & 0xff;
        const uint8_t g = (ac.pixels[p] >> 8) & 0xff;
        const uint8_t b = ac.pixels[p] & 0xff;
        fprintf(f, "%d %d %d\n", r, g, b);
    }

    fclose(f);

    return 0;
}

#endif // PLATFORM_C


#endif // ALDRIN_H_