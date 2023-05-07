#ifndef ALDRIN_H_
#define ALDRIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))


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


void aldrin_put_pixel(uint32_t *canvas, uint32_t width,
    uint32_t x, uint32_t y, uint32_t color) {

        canvas[y*width+x] = color;
}


void aldrin_fill(uint32_t *canvas, uint32_t width, uint32_t height,
    uint32_t fill_color) {

    for (uint32_t p = 0; p < width*height; ++p) {
        canvas[p] = fill_color;
    }
}


void aldrin_calculate_line_formula(uint32_t x1, uint32_t y1, int dx, int dy, double *m, double *c) {
    *m = ((double) dy) / dx;
    *c = y1 - (*m)*x1;
}


// TODO: add smooth curves to top and bottom of line if thickness is greater than 1
// KNOWN ERROR: when the line is near by one of edges and thickness is big, /
// it causes negative indices and Segmentation fault
void aldrin_draw_line(uint32_t *canvas, uint32_t width,
    uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t line_color, uint32_t thickness) {
    
    const int dx = x1-x2;
    const int dy = y1-y2;
    double m, c;
    aldrin_calculate_line_formula(x1, y1, dx, dy, &m, &c);

    if (abs(dx) > abs(dy)) {
        // it is horizontal-ish
        // f(x) = y = mx + c

        for (uint32_t x = min(x1, x2); x <= max(x1, x2); ++x) {
            uint32_t y = m*x + c;

            aldrin_put_pixel(canvas, width, x, y, line_color);

            for (int i = 1; i < thickness; ++i) {
                if (fmod((double) i/2, 1) == 0) {
                    aldrin_put_pixel(canvas, width, x, y-i+i/2, line_color);
                } else {
                    aldrin_put_pixel(canvas, width, x, y+i-i/2, line_color);
                }
            }
        }

    } else {
        // it is vertical-ish
        // f(y) = x = (y - c) / m

        for (uint32_t y = min(y1, y2); y <= max(y1, y2); ++y) {
            uint32_t x = (y - c) / m;

            aldrin_put_pixel(canvas, width, x, y, line_color);

            for (int i = 1; i < thickness; ++i) {
                if (fmod((double) i/2, 1) == 0) {
                    aldrin_put_pixel(canvas, width, x-i+i/2, y, line_color);
                } else {
                    aldrin_put_pixel(canvas, width, x+i-i/2, y, line_color);
                }
            }
        }
    }

}


void aldrin_draw_triangle(uint32_t *canvas, uint32_t width,
    uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t x3, uint32_t y3,
    uint32_t line_color, uint32_t thickness) {

    aldrin_draw_line(canvas, width, x1, y1, x2, y2, line_color, thickness);
    aldrin_draw_line(canvas, width, x1, y1, x3, y3, line_color, thickness);
    aldrin_draw_line(canvas, width, x2, y2, x3, y3, line_color, thickness);
}


void aldrin_fill_triangle(uint32_t *canvas, uint32_t width,
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
        const uint32_t x_start = (y - c13) / m13;
        const uint32_t x_end = (y - c12) / m12;
        aldrin_draw_line(canvas, width, x_start, y, x_end, y, fill_color, 1);
    }

    // scan and fill second half
    for (uint32_t y = y2; y <= y3; ++y) {

        // f(y) = x = (y - c) / m
        const uint32_t x_start = (y - c13) / m13;
        const uint32_t x_end = (y - c23) / m23;
        aldrin_draw_line(canvas, width, x_start, y, x_end, y, fill_color, 1);
    }

}


int aldrin_save_ppm(uint32_t *canvas, uint32_t width, uint32_t height,
    const char *filename) {
    FILE *f = fopen(filename, "wb");
    if (f == NULL) {
        printf("Cannot open output file %s.\n", filename);
        return 1;
    }

    fprintf(f, "P3\n%d %d 255\n", width, height);

    for (uint32_t p = 0; p < width*height; ++p) {
        const uint8_t r = (canvas[p] >> 16) & 0xff;
        const uint8_t g = (canvas[p] >> 8) & 0xff;
        const uint8_t b = canvas[p] & 0xff;
        fprintf(f, "%d %d %d\n", r, g, b);
    }

    fclose(f);

    return 0;
}


#endif // ALDRIN_H_