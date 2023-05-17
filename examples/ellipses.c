#include <stdint.h>
#include "../src/aldrin.c"

#define WIDTH 200
#define HEIGHT 200

static uint32_t pixels[WIDTH*HEIGHT];

Aldrin_Canvas ac = { pixels, WIDTH, HEIGHT };

int main() {
    aldrin_fill_ellipse(ac, 0, 0, 90, 50, 0x0ff0000);
    aldrin_fill_ellipse(ac, 190, 0, 90, 50, 0x000ff00);
    aldrin_draw_ellipse(ac, 0, 190, 90, 50, 0x00000ff);
    aldrin_fill_ellipse(ac, 190, 190, 90, 50, 0x0ffffff);

    #ifdef PLATFORM_C
    aldrin_save_ppm(ac, "output/ellipses.ppm");
    #endif // PLATFORM_C

    return 0;
}