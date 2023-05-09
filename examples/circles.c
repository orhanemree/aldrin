#include <stdint.h>
#include "../src/aldrin.c"

#define WIDTH 200
#define HEIGHT 200

static uint32_t pixels[WIDTH*HEIGHT];

Aldrin_Canvas ac = { pixels, WIDTH, HEIGHT };

int main() {
    aldrin_fill_circle(ac, 0, 0, 90, 0x0ff0000);
    aldrin_draw_circle(ac, WIDTH/2, HEIGHT/2, 80, 0x00ff00);

    const int r = 25;
    aldrin_fill_circle(ac, WIDTH-r-1, HEIGHT-r-1, r, 0x0000ff);

    aldrin_save_ppm(ac, "output/circles.ppm");

    return 0;
}