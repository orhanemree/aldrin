<p align="center">
    <img src="img/lily_aldrin.png">
</p>

# 👩‍🦰 Aldrin
Simple 2D Computer Graphics Library in C.

It stores some color codes in memory (called canvas here) and you are free to use this pixels wherever you want. 

## Quick Start
* Just copy and paste `/src` folder to your project.
```c
#include "src/aldrin.c" // that's it!
```

## `Hello, World!` of Pixels
```c
#include <stdint.h>
#include "src/aldrin.c"

#define WIDTH 160
#define HEIGHT 90

static uint32_t pixels[WIDTH*HEIGHT];

int main() {
    Aldrin_Canvas ac = { pixels, WIDTH, HEIGHT };
    aldrin_fill(ac, 0xff00ff);
    aldrin_save_ppm(ac, "img/hello_world.ppm");
    return 0;
}
```
Output should look something like:

<img src="img/hello_world.png">

Note that: `aldrin_save_ppm()` function generates `.ppm` output (see [`/img/hello_world.ppm`](img/hello_world.ppm)). The output converted to `.png` format to be displayed here.

## Examples
* See [/examples](examples).

## Documentation
* See [DOCUMENTATION.md](DOCUMENTATION.md).

## References
* [Gabriel Gambetta / Computer Graphics from Scratch](https://gabrielgambetta.com/computer-graphics-from-scratch/)
* [Tsoding / Graphics Library in C [Video]](https://youtu.be/LmQKZmQh1ZQ)
* ChatGPT of course :D

## License
* Licensed under the [MIT License](LICENSE).