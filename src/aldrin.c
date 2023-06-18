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
#endif // PLATFORM_C

#include <stdint.h>

// basic math functions implementation
// so we don't need to link external math library
#define ac_min(a,b) ((int)(a)<(int)(b)?(a):(b))
#define ac_max(a,b) ((int)(a)>(int)(b)?(a):(b))
#define ac_abs(n) ((int)(n)>=0?(n):(-1*(n)))

uint32_t ac_pow(uint32_t a, uint32_t b) {
    if (b == 0) return 1;
    if (b > 1) return a * ac_pow(a, b-1);
    return a;
}

double ac_sqrt(double x) {
    double guess = x / 2.0;
    double error = 0.0001;
    while (ac_abs(guess * guess - x) > error) {
        guess = (guess + x / guess) / 2.0;
    }
    return guess;
}

double ac_fmod(double x, double y) {
    double quotient = x / y;
    double remainder = x - ((int) quotient * y);
    return remainder;
}


// basic 3*5 font implementation
#define AC_GLYPHS_WIDTH 3
#define AC_GLYPHS_HEIGHT 5
#define AC_TEXT_SPACING 1

static char aldrin_glyphs[77][AC_GLYPHS_HEIGHT][AC_GLYPHS_WIDTH] = {
    { /*A*/ {1, 1, 1}, {1, 0, 1}, {1, 1, 1}, {1, 0, 1}, {1, 0, 1}},
    { /*B*/ {1, 1, 0}, {1, 0, 1}, {1, 1, 1}, {1, 0, 1}, {1, 1, 0}},
    { /*C*/ {1, 1, 1}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0}, {1, 1, 1}},
    { /*D*/ {1, 1, 0}, {1, 0, 1}, {1, 0, 1}, {1, 0, 1}, {1, 1, 0}},
    { /*E*/ {1, 1, 1}, {1, 0, 0}, {1, 1, 1}, {1, 0, 0}, {1, 1, 1}},
    { /*F*/ {1, 1, 1}, {1, 0, 0}, {1, 1, 1}, {1, 0, 0}, {1, 0, 0}},
    { /*G*/ {1, 1, 1}, {1, 0, 0}, {1, 0, 1}, {1, 0, 1}, {1, 1, 1}},
    { /*H*/ {1, 0, 1}, {1, 0, 1}, {1, 1, 1}, {1, 0, 1}, {1, 0, 1}},
    { /*I*/ {1, 1, 1}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}, {1, 1, 1}},
    { /*J*/ {1, 1, 0}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}, {1, 0, 0}},
    { /*K*/ {1, 0, 1}, {1, 0, 1}, {1, 1, 0}, {1, 0, 1}, {1, 0, 1}},
    { /*L*/ {1, 0, 0}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0}, {1, 1, 1}},
    { /*M*/ {1, 0, 1}, {1, 1, 1}, {1, 0, 1}, {1, 0, 1}, {1, 0, 1}},
    { /*N*/ {1, 0, 1}, {1, 0, 1}, {1, 0, 1}, {1, 1, 1}, {1, 0, 1}},
    { /*O*/ {1, 1, 1}, {1, 0, 1}, {1, 0, 1}, {1, 0, 1}, {1, 1, 1}},
    { /*P*/ {1, 1, 1}, {1, 0, 1}, {1, 1, 1}, {1, 0, 0}, {1, 0, 0}},
    { /*Q*/ {1, 1, 1}, {1, 0, 1}, {1, 0, 1}, {1, 1, 1}, {1, 1, 0}},
    { /*R*/ {1, 1, 1}, {1, 0, 1}, {1, 1, 1}, {1, 1, 0}, {1, 0, 1}},
    { /*S*/ {0, 1, 1}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {1, 1, 0}},
    { /*T*/ {1, 1, 1}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}},
    { /*U*/ {1, 0, 1}, {1, 0, 1}, {1, 0, 1}, {1, 0, 1}, {1, 1, 1}},
    { /*V*/ {1, 0, 1}, {1, 0, 1}, {1, 0, 1}, {1, 0, 1}, {0, 1, 0}},
    { /*W*/ {1, 0, 1}, {1, 0, 1}, {1, 0, 1}, {1, 1, 1}, {1, 0, 1}},
    { /*X*/ {1, 0, 1}, {1, 0, 1}, {0, 1, 0}, {1, 0, 1}, {1, 0, 1}},
    { /*Y*/ {1, 0, 1}, {1, 0, 1}, {1, 0, 1}, {0, 1, 0}, {0, 1, 0}},
    { /*Z*/ {1, 1, 1}, {0, 0, 1}, {0, 1, 0}, {1, 0, 0}, {1, 1, 1}},
    { /*a*/ {1, 1, 0}, {0, 0, 1}, {0, 1, 1}, {1, 0, 1}, {0, 1, 1}},
    { /*b*/ {1, 0, 0}, {1, 0, 0}, {1, 1, 0}, {1, 0, 1}, {1, 1, 0}},
    { /*c*/ {0, 0, 0}, {0, 1, 1}, {1, 0, 0}, {1, 0, 0}, {0, 1, 1}},
    { /*d*/ {0, 0, 1}, {0, 0, 1}, {0, 1, 1}, {1, 0, 1}, {0, 1, 1}},
    { /*e*/ {0, 1, 1}, {1, 0, 1}, {1, 1, 1}, {1, 0, 0}, {0, 1, 1}},
    { /*f*/ {0, 0, 0}, {0, 1, 1}, {0, 1, 0}, {1, 1, 1}, {0, 1, 0}},
    { /*g*/ {0, 1, 1}, {1, 0, 1}, {1, 1, 1}, {0, 0, 1}, {1, 1, 0}},
    { /*h*/ {1, 0, 0}, {1, 0, 0}, {1, 1, 0}, {1, 0, 1}, {1, 0, 1}},
    { /*i*/ {0, 1, 0}, {0, 0, 0}, {1, 1, 0}, {0, 1, 0}, {0, 1, 0}},
    { /*j*/ {0, 0, 0}, {1, 1, 0}, {0, 1, 0}, {0, 1, 0}, {1, 0, 0}},
    { /*k*/ {1, 0, 0}, {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 0, 1}},
    { /*l*/ {0, 1, 0}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}},
    { /*m*/ {0, 0, 0}, {0, 0, 0}, {1, 1, 1}, {1, 1, 1}, {1, 0, 1}},
    { /*n*/ {0, 0, 0}, {0, 0, 0}, {1, 1, 1}, {1, 0, 1}, {1, 0, 1}},
    { /*o*/ {0, 0, 0}, {0, 0, 0}, {1, 1, 1}, {1, 0, 1}, {1, 1, 1}},
    { /*p*/ {0, 0, 0}, {1, 1, 1}, {1, 0, 1}, {1, 1, 1}, {1, 0, 0}},
    { /*q*/ {0, 0, 0}, {1, 1, 1}, {1, 0, 1}, {1, 1, 1}, {0, 0, 1}},
    { /*r*/ {0, 0, 0}, {0, 1, 0}, {1, 0, 1}, {1, 0, 0}, {1, 0, 0}},
    { /*s*/ {0, 1, 1}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {1, 1, 0}},
    { /*t*/ {0, 1, 0}, {1, 1, 1}, {0, 1, 0}, {0, 1, 0}, {0, 0, 1}},
    { /*u*/ {0, 0, 0}, {0, 0, 0}, {1, 0, 1}, {1, 0, 1}, {1, 1, 1}},
    { /*v*/ {0, 0, 0}, {0, 0, 0}, {1, 0, 1}, {1, 0, 1}, {0, 1, 0}},
    { /*w*/ {0, 0, 0}, {0, 0, 0}, {1, 0, 1}, {1, 1, 1}, {0, 1, 0}},
    { /*x*/ {0, 0, 0}, {0, 0, 0}, {1, 0, 1}, {0, 1, 0}, {1, 0, 1}},
    { /*y*/ {0, 0, 0}, {1, 0, 1}, {1, 0, 1}, {0, 1, 0}, {0, 1, 0}},
    { /*z*/ {0, 0, 0}, {0, 0, 0}, {1, 1, 1}, {0, 1, 0}, {1, 1, 1}},
    { /*0*/ {0, 1, 0}, {1, 0, 1}, {1, 0, 1}, {1, 0, 1}, {0, 1, 0}},
    { /*1*/ {0, 0, 1}, {0, 1, 1}, {0, 0, 1}, {0, 0, 1}, {0, 0, 1}},
    { /*2*/ {0, 1, 0}, {1, 0, 1}, {0, 0, 1}, {0, 1, 0}, {1, 1, 1}},
    { /*3*/ {1, 1, 0}, {0, 0, 1}, {0, 1, 0}, {0, 0, 1}, {1, 1, 0}},
    { /*4*/ {1, 0, 1}, {1, 0, 1}, {1, 1, 1}, {0, 0, 1}, {0, 0, 1}},
    { /*5*/ {1, 1, 1}, {1, 0, 0}, {1, 1, 0}, {0, 0, 1}, {1, 1, 0}},
    { /*6*/ {0, 1, 1}, {1, 0, 0}, {1, 1, 0}, {1, 0, 1}, {1, 1, 0}},
    { /*7*/ {1, 1, 1}, {0, 0, 1}, {0, 1, 0}, {1, 0, 0}, {1, 0, 0}},
    { /*8*/ {1, 1, 1}, {1, 0, 1}, {1, 1, 1}, {1, 0, 1}, {1, 1, 1}},
    { /*9*/ {0, 1, 1}, {1, 0, 1}, {0, 1, 1}, {0, 0, 1}, {1, 1, 0}},
    { /* */ {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    { /*+*/ {0, 0, 0}, {0, 0, 0}, {0, 1, 0}, {1, 1, 1}, {0, 1, 0}},
    { /*-*/ {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {1, 1, 1}, {0, 0, 0}},
    { /***/ {0, 0, 0}, {0, 0, 0}, {1, 0, 1}, {0, 1, 0}, {1, 0, 1}},
    { /*/*/ {0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 0}, {1, 0, 0}},
    { /*.*/ {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 1, 0}},
    { /*,*/ {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 1}, {0, 1, 0}},
    { /*!*/ {0, 1, 0}, {0, 1, 0}, {0, 1, 0}, {0, 0, 0}, {0, 1, 0}},
    { /*?*/ {1, 1, 0}, {0, 0, 1}, {0, 1, 0}, {0, 0, 0}, {0, 1, 0}},
    { /*\*/ {0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 1, 0}, {0, 0, 1}},
    { /*_*/ {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {1, 1, 1}},
    { /*:*/ {0, 1, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 1, 0}},
    { /*;*/ {0, 1, 0}, {0, 0, 0}, {0, 0, 0}, {0, 1, 0}, {1, 0, 0}},
    { /*'*/ {0, 1, 0}, {0, 1, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    { /*"*/ {1, 0, 1}, {1, 0, 1}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
};


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

    if (ac_abs(dx) > ac_abs(dy)) {
        // it is horizontal-ish
        // f(x) = y = mx + c
        
        for (uint32_t x = ac_max(ac_min(x1, x2), 0); x <= ac_min(ac_max(x1, x2), ac.width-1); ++x) {
            int y = m*x + c, yt;

            if (y >= (int) ac_max(ac_min(y1, y2), 0) && y <= (int) ac_min(ac_max(y1, y2), ac.height-1)) {
                aldrin_put_pixel(ac, x, y, line_color);
            }

            for (int i = 1; i < (int) thickness; ++i) {
                yt = (ac_fmod((double) i/2, 1) == 0) ? y-i+i/2 : y+i-i/2;
                if (yt >= 0 && yt < (int) ac.height) {
                    aldrin_put_pixel(ac, x, yt, line_color);
                }
            }
        }

    } else {
        // it is vertical-ish
        // f(y) = x = (y - c) / m

        for (uint32_t y = ac_max(ac_min(y1, y2), 0); y <= ac_min(ac_max(y1, y2), ac.height-1); ++y) {
            int x, xt;
            x = dx == 0 ? x1 : (y - c) / m;

            if (x >= (int) ac_max(ac_min(x1, x2), 0) && x <= (int) ac_min(ac_max(x1, x2), ac.width-1)) {
                aldrin_put_pixel(ac, x, y, line_color);
            }

            for (int i = 1; i < (int) thickness; ++i) {
                xt = (ac_fmod((double) i/2, 1) == 0) ? x-i+i/2 : x+i-i/2;

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
void aldrin_draw_ellipse(Aldrin_Canvas ac, uint32_t x, uint32_t y,
    uint32_t rx, uint32_t ry, uint32_t line_color) {

    if (rx == 0) rx = 1;
    if (ry == 0) ry = 1;

    // implementation of fucking midpoint ellipse algorithm
    int xk0, xk1, yk0, yk1, p1k0, p1k1, p2k0, p2k1;
    uint32_t px, py;

    // region 1
    xk0 = 0;
    yk0 = ry;
    p1k0 = ac_pow(ry, 2)+ac_pow(rx, 2)/4-ry*ac_pow(rx, 2);

    do {
        px = xk0+x;
        py = yk0+y;

        // repeat for 4 quads
        if (px >= 0 && px < ac.width) {
            if (py >= 0 && py < ac.height) {
                aldrin_put_pixel(ac, px, py, line_color);
            }
            if (y-py+y >= 0 && y-py+y < ac.height) {
                aldrin_put_pixel(ac, px, y-py+y, line_color);
            }
        }
        if (x-px+x >= 0 && x-px+x < ac.width) {
            if (py >= 0 && py < ac.height) {
                aldrin_put_pixel(ac, x-px+x, py, line_color);
            }
            if (y-py+y >= 0 && y-py+y < ac.height) {
                aldrin_put_pixel(ac, x-px+x, y-py+y, line_color);
            }
        }

        if (p1k0 >= 0) {
            xk1 = xk0+1;
            yk1 = yk0-1;
        } else {
            xk1 = xk0+1;
            yk1 = yk0;
        }
        p1k1 = p1k0+ac_pow(ry, 2)+2*(xk0+1)*ac_pow(ry, 2)+ac_pow(rx, 2)*(ac_pow(yk1, 2)-ac_pow(yk0, 2))-ac_pow(rx, 2)*(yk1-yk0);

        xk0 = xk1;
        yk0 = yk1;
        p1k0 = p1k1;


    } while (2*ac_pow(ry, 2)*xk1 < 2*ac_pow(rx, 2)*yk1);

    // region 2
    int cond;
    p2k0 = ac_pow(xk0+1/2, 2)*ac_pow(ry, 2)+ac_pow(yk0-1, 2)*ac_pow(rx, 2)-ac_pow(rx*ry, 2);

    do {
        cond = yk0 > 0;

        px = xk0+x;
        py = yk0+y;

        // repeat for 4 quads
        if (px >= 0 && px < ac.width) {
            if (py >= 0 && py < ac.height) {
                aldrin_put_pixel(ac, px, py, line_color);
            }
            if (y-py+y >= 0 && y-py+y < ac.height) {
                aldrin_put_pixel(ac, px, y-py+y, line_color);
            }
        }
        if (x-px+x >= 0 && x-px+x < ac.width) {
            if (py >= 0 && py < ac.height) {
                aldrin_put_pixel(ac, x-px+x, py, line_color);
            }
            if (y-py+y >= 0 && y-py+y < ac.height) {
                aldrin_put_pixel(ac, x-px+x, y-py+y, line_color);
            }
        }

        if (p2k0 >= 0) {
            xk1 = xk0;
            yk1 = yk0-1;
        } else {
            xk1 = xk0+1;
            yk1 = yk0-1;
        }
        p2k1 = p2k0+ac_pow(rx, 2)-2*ac_pow(rx, 2)*(yk0-1)+ac_pow(ry, 2)*(ac_pow(xk1, 2)-ac_pow(xk0, 2))+ac_pow(ry, 2)*(xk1-xk0);

        xk0 = xk1;
        yk0 = yk1;
        p2k0 = p2k1;

    } while (cond);
}


void aldrin_fill_ellipse(Aldrin_Canvas ac, uint32_t x, uint32_t y,
    uint32_t rx, uint32_t ry, uint32_t fill_color) {

    if (rx == 0) rx = 1;
    if (ry == 0) ry = 1;

    int xk0, xk1, yk0, yk1, p1k0, p1k1, p2k0, p2k1;
    uint32_t px, py;

    // region 1
    xk0 = 0;
    yk0 = ry;
    p1k0 = ac_pow(ry, 2)+ac_pow(rx, 2)/4-ry*ac_pow(rx, 2);

    do {
        px = xk0+x;
        py = yk0+y;
    
        // repeat for 4 quads
        aldrin_draw_line(ac, ac_min(px, ac.width-1), ac_min(py, ac.height-1), 
            ac_min(x, ac.width-1), ac_min(py, ac.height-1), fill_color, 1);

        aldrin_draw_line(ac, ac_min(px, ac.width-1), ac_max(y-py+y, 0), 
            ac_min(x, ac.width-1), ac_max(y-py+y, 0), fill_color, 1);

        aldrin_draw_line(ac, ac_max(x-px+x, 0), ac_min(py, ac.height-1), 
            ac_min(x, ac.width-1), ac_min(py, ac.height-1), fill_color, 1);

        aldrin_draw_line(ac, ac_max(x-px+x, 0), ac_max(y-py+y, 0), 
            ac_min(x, ac.width-1), ac_max(y-py+y, 0), fill_color, 1);

        if (p1k0 >= 0) {
            xk1 = xk0+1;
            yk1 = yk0-1;
        } else {
            xk1 = xk0+1;
            yk1 = yk0;
        }
        p1k1 = p1k0+ac_pow(ry, 2)+2*(xk0+1)*ac_pow(ry, 2)+ac_pow(rx, 2)*(ac_pow(yk1, 2)-ac_pow(yk0, 2))-ac_pow(rx, 2)*(yk1-yk0);

        xk0 = xk1;
        yk0 = yk1;
        p1k0 = p1k1;


    } while (2*ac_pow(ry, 2)*xk1 < 2*ac_pow(rx, 2)*yk1);

    // region 2
    int cond;
    p2k0 = ac_pow(xk0+1/2, 2)*ac_pow(ry, 2)+ac_pow(yk0-1, 2)*ac_pow(rx, 2)-ac_pow(rx*ry, 2);
    
    do {
         cond = yk0 > 0;

        px = xk0+x;
        py = yk0+y;

        // repeat for 4 quads
        aldrin_draw_line(ac, ac_min(px, ac.width-1), ac_min(py, ac.height-1), 
            ac_min(x, ac.width-1), ac_min(py, ac.height-1), fill_color, 1);

        aldrin_draw_line(ac, ac_min(px, ac.width-1), ac_max(y-py+y, 0), 
            ac_min(x, ac.width-1), ac_max(y-py+y, 0), fill_color, 1);

        aldrin_draw_line(ac, ac_max(x-px+x, 0), ac_min(py, ac.height-1), 
            ac_min(x, ac.width-1), ac_min(py, ac.height-1), fill_color, 1);

        aldrin_draw_line(ac, ac_max(x-px+x, 0), ac_max(y-py+y, 0), 
            ac_min(x, ac.width-1), ac_max(y-py+y, 0), fill_color, 1);

        if (p2k0 >= 0) {
            xk1 = xk0;
            yk1 = yk0-1;
        } else {
            xk1 = xk0+1;
            yk1 = yk0-1;
        }
        p2k1 = p2k0+ac_pow(rx, 2)-2*ac_pow(rx, 2)*(yk0-1)+ac_pow(ry, 2)*(ac_pow(xk1, 2)-ac_pow(xk0, 2))+ac_pow(ry, 2)*(xk1-xk0);

        xk0 = xk1;
        yk0 = yk1;
        p2k0 = p2k1;

    } while (cond);
}


void aldrin_draw_circle(Aldrin_Canvas ac, uint32_t x, uint32_t y, uint32_t r,
    uint32_t line_color) {

    aldrin_draw_ellipse(ac, x, y, r, r, line_color);
}


void aldrin_fill_circle(Aldrin_Canvas ac, uint32_t x, uint32_t y, uint32_t r,
    uint32_t fill_color) {

    aldrin_fill_ellipse(ac, x, y, r, r, fill_color);
}


void aldrin_draw_rectangle(Aldrin_Canvas ac, uint32_t x, int32_t y,
    uint32_t w, uint32_t h, uint32_t line_color, uint32_t thickness) {
    
    const uint32_t half_w = w/2;
    const uint32_t half_h = h/2;

    // calculate bounding box
    const uint32_t x_min = ac_max(x-half_w, 0);
    const uint32_t y_min = ac_max(y-half_h, 0);
    const uint32_t x_max = ac_min(x+half_w, ac.width-1);
    const uint32_t y_max = ac_min(y+half_h, ac.height-1);

    if (half_h <= y) {
        // top
        aldrin_draw_line(ac, x_min, y_min, x_max, y_min, line_color, thickness);
    }

    if (half_w <= x) {
        // left
        aldrin_draw_line(ac, x_min, y_max, x_min, y_min, line_color, thickness);
    }

    if (x+half_w <= ac.width) {
        // right
        aldrin_draw_line(ac, x_max, y_min, x_max, y_max, line_color, thickness);
    }

    if (y+half_h <= ac.height) {
        // bottom
        aldrin_draw_line(ac, x_max, y_max, x_min, y_max, line_color, thickness);
    }
}


void aldrin_fill_rectangle(Aldrin_Canvas ac, uint32_t x, int32_t y,
    uint32_t w, uint32_t h, uint32_t fill_color) {

    const uint32_t half_w = w/2;
    const uint32_t half_h = h/2;

    // calculate bounding box
    const uint32_t x_min = ac_max(x-half_w, 0);
    const uint32_t y_min = ac_max(y-half_h, 0);
    const uint32_t x_max = ac_min(x+half_w, ac.width-1);
    const uint32_t y_max = ac_min(y+half_h, ac.height-1);

    for (uint32_t y0 = y_min; y0 <= y_max; ++y0) {
        aldrin_draw_line(ac, x_min, y0, x_max, y0, fill_color, 1); 
    }
}


void aldrin_draw_square(Aldrin_Canvas ac, uint32_t x, int32_t y, uint32_t l,
    uint32_t line_color, uint32_t thickness) {
    
    aldrin_draw_rectangle(ac, x, y, l, l, line_color, thickness);
}


void aldrin_fill_square(Aldrin_Canvas ac, uint32_t x, int32_t y, uint32_t l,
    uint32_t fill_color) {
    
    aldrin_fill_rectangle(ac, x, y, l, l, fill_color);
}


void aldrin_text(Aldrin_Canvas ac, uint32_t x, int32_t y, const char *text,
    uint32_t text_color, uint32_t text_size) {

    int glyph_index, x_temp, y_temp, ignored = 0;

    // write corresponding glyph for every char
    for (int i = 0; text[i] != '\0'; ++i) {
        switch (text[i]) {
            case 'A': glyph_index = 0; break;
            case 'B': glyph_index = 1; break;
            case 'C': glyph_index = 2; break;
            case 'D': glyph_index = 3; break;
            case 'E': glyph_index = 4; break;
            case 'F': glyph_index = 5; break;
            case 'G': glyph_index = 6; break;
            case 'H': glyph_index = 7; break;
            case 'I': glyph_index = 8; break;
            case 'J': glyph_index = 9; break;
            case 'K': glyph_index = 10; break;
            case 'L': glyph_index = 11; break;
            case 'M': glyph_index = 12; break;
            case 'N': glyph_index = 13; break;
            case 'O': glyph_index = 14; break;
            case 'P': glyph_index = 15; break;
            case 'Q': glyph_index = 16; break;
            case 'R': glyph_index = 17; break;
            case 'S': glyph_index = 18; break;
            case 'T': glyph_index = 19; break;
            case 'U': glyph_index = 20; break;
            case 'V': glyph_index = 21; break;
            case 'W': glyph_index = 22; break;
            case 'X': glyph_index = 23; break;
            case 'Y': glyph_index = 24; break;
            case 'Z': glyph_index = 25; break;
            case 'a': glyph_index = 26; break;
            case 'b': glyph_index = 27; break;
            case 'c': glyph_index = 28; break;
            case 'd': glyph_index = 29; break;
            case 'e': glyph_index = 30; break;
            case 'f': glyph_index = 31; break;
            case 'g': glyph_index = 32; break;
            case 'h': glyph_index = 33; break;
            case 'i': glyph_index = 34; break;
            case 'j': glyph_index = 35; break;
            case 'k': glyph_index = 36; break;
            case 'l': glyph_index = 37; break;
            case 'm': glyph_index = 38; break;
            case 'n': glyph_index = 39; break;
            case 'o': glyph_index = 40; break;
            case 'p': glyph_index = 41; break;
            case 'q': glyph_index = 42; break;
            case 'r': glyph_index = 43; break;
            case 's': glyph_index = 44; break;
            case 't': glyph_index = 45; break;
            case 'u': glyph_index = 46; break;
            case 'v': glyph_index = 47; break;
            case 'w': glyph_index = 48; break;
            case 'x': glyph_index = 49; break;
            case 'y': glyph_index = 50; break;
            case 'z': glyph_index = 51; break;
            case '0': glyph_index = 52; break;
            case '1': glyph_index = 53; break;
            case '2': glyph_index = 54; break;
            case '3': glyph_index = 55; break;
            case '4': glyph_index = 56; break;
            case '5': glyph_index = 57; break;
            case '6': glyph_index = 58; break;
            case '7': glyph_index = 59; break;
            case '8': glyph_index = 60; break;
            case '9': glyph_index = 61; break;
            case ' ': glyph_index = 62; break;
            case '+': glyph_index = 63; break;
            case '-': glyph_index = 64; break;
            case '*': glyph_index = 65; break;
            case '/': glyph_index = 66; break;
            case '.': glyph_index = 67; break;
            case ',': glyph_index = 68; break;
            case '!': glyph_index = 69; break;
            case '?': glyph_index = 70; break;
            case '\\': glyph_index = 71; break;
            case '_': glyph_index = 72; break;
            case ':': glyph_index = 73; break;
            case ';': glyph_index = 74; break;
            case '\'': glyph_index = 75; break;
            case '"': glyph_index = 76; break;

            default:
                // do not display anything if char is unknown
                ++ignored; break;
        }

        // vertical
        y_temp = y;
        for (int j = 0; j < AC_GLYPHS_HEIGHT*text_size; ++j) {
            // horizontal
            x_temp = x + (i-ignored) * (AC_GLYPHS_WIDTH+AC_TEXT_SPACING)*text_size;
            for (int k = 0; k < AC_GLYPHS_WIDTH*text_size; ++k) {
                // color if need to color the pixel according to glyph table
                if (aldrin_glyphs[glyph_index][j/text_size][k/text_size] && x_temp < ac.width && y_temp < ac.height) {
                    aldrin_put_pixel(ac, x_temp, y_temp, text_color);
                }
                ++x_temp;
            }
            ++y_temp;
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