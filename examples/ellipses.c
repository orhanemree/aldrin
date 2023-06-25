#include <stdint.h>
#include "../src/aldrin.c"

#define WIDTH 200
#define HEIGHT 200

static uint32_t pixels[WIDTH*HEIGHT];

Aldrin_Canvas ac = { pixels, WIDTH, HEIGHT };

int main() {
    aldrin_fill_ellipse(ac, 0, 0, 10, 50, 0x00ff00);
    aldrin_fill_ellipse(ac, 100, 100, 110, 50, 0xff0000);
    aldrin_draw_ellipse(ac, 0, 190, 90, 50, 0x0000ff);

    const int r = 20;
    aldrin_fill_circle(ac, 100-r, 100-r, r, 0xffffff);

    #ifdef PLATFORM_C
    aldrin_save_ppm(ac, "output/ellipses.ppm");
    #endif // PLATFORM_C

    return 0;
}