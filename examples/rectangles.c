#include <stdint.h>
#include "../src/aldrin.c"

#define WIDTH 200
#define HEIGHT 200

static uint32_t pixels[WIDTH*HEIGHT];

Aldrin_Canvas ac = { pixels, WIDTH, HEIGHT };

int main() {
    aldrin_draw_rectangle(ac, 0, 0, 200, 100, 0x0000ff, 1);
    aldrin_fill_rectangle(ac, 0, 0, 190, 90, 0xff0000);

    aldrin_fill_square(ac, 205, 205, 100, 0x00ff00);
    aldrin_draw_square(ac, 105, 105, 50, 0xffffff, 2);

    #ifdef PLATFORM_C
    aldrin_save_ppm(ac, "output/rectangles.ppm");
    #endif // PLATFORM_C

    return 0;
}