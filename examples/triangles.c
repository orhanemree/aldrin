#include <stdint.h>
#include "../src/aldrin.c"

#define WIDTH 200
#define HEIGHT 200

static uint32_t pixels[WIDTH*HEIGHT];

Aldrin_Canvas ac = { pixels, WIDTH, HEIGHT };

int main() {
    aldrin_fill_triangle(ac, 5, 10, 5, 100, 120, 10, 0xff0000);
    aldrin_fill_triangle(ac, 80, 80, 50, 130, 130, 90, 0x00ff00);
    aldrin_fill_triangle(ac, WIDTH-10, 20, 90, 190, 130, 150, 0x0000ff);

    aldrin_save_ppm(ac, "output/triangles.ppm");

    return 0;
}