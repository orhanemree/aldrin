#include <stdint.h>
#include "../src/aldrin.c"

#define WIDTH 200
#define HEIGHT 200

static uint32_t pixels[WIDTH*HEIGHT];

Aldrin_Canvas ac = { pixels, WIDTH, HEIGHT };

int main() {
    aldrin_text(ac, 0, 0, "abcdefghijklmnopqrstuvwxyz", 0xffffff, 1);
    // AC_GLYPHS_HEIGHT is 5 by default
    aldrin_text(ac, 0, AC_GLYPHS_HEIGHT, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 0xff0000, 2);
    aldrin_text(ac, 20, 4*AC_GLYPHS_HEIGHT, "01234 56789", 0x00ff00, 3);

    /*
    multiply them to center text horizontally to canvas:
        7: text length
        AC_GLYPHS_WIDTH: 3 pixels by default in the library
        AC_TEXT_SPACING: 1 pixel by default in the library
        5: font size specified as function param
    */
    const int x = 7*(AC_GLYPHS_WIDTH+AC_TEXT_SPACING)*5;
    aldrin_text(ac, (WIDTH-x)/2, 100, "+-*/\\.,", 0x0000ff, 5);
    aldrin_text(ac, (WIDTH-x)/2, 150, "_?!'\":;", 0x0000ff, 5);
    
    #ifdef PLATFORM_C
    aldrin_save_ppm(ac, "output/text.ppm");
    #endif // PLATFORM_C
    
    return 0;
}