#include <stdint.h>
#include "../src/aldrin.c"

#define WIDTH 200
#define HEIGHT 200

static uint32_t pixels[WIDTH*HEIGHT];

Aldrin_Canvas ac = { pixels, WIDTH, HEIGHT };

int main() {
    aldrin_draw_rectangle(ac, 100, 100, 200, 105, 0x0000ff, 2);
    aldrin_fill_rectangle(ac, 0, 0, 50, 90, 0xff0000);

    aldrin_fill_square(ac, 100, 100, 50, 0x00ff00);
    aldrin_draw_square(ac, 250, 250, 50, 0xffffff, 2);

    #ifdef PLATFORM_C
    aldrin_save_ppm(ac, "output/rectangles.ppm");
    #endif // PLATFORM_C

    return 0;
}