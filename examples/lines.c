#include <stdint.h>
#include "../src/aldrin.c"

#define WIDTH 200
#define HEIGHT 200

static uint32_t pixels[WIDTH*HEIGHT];

Aldrin_Canvas ac = { pixels, WIDTH, HEIGHT };

int main() {
    aldrin_draw_line(ac, WIDTH-1, HEIGHT-1, WIDTH/2-1, 0, 0xff0000, 3);
    aldrin_draw_line(ac, WIDTH/2-1, HEIGHT-1, 0, 0, 0x00ff00, 1);
    aldrin_draw_line(ac, 0, 0, WIDTH-1, 0, 0x0000ff, 1);
    aldrin_draw_line(ac, 0, 0, 0, HEIGHT-1, 0x0000ff, 1);

    #ifdef PLATFORM_C
    aldrin_save_ppm(ac, "output/lines.ppm");
    #endif // PLATFORM_C
    
    return 0;
}