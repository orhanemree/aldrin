<p align="center">
    <img src="img/lily_aldrin.png">
</p>

# 👩‍🦰 Aldrin
Simple 2D Computer Graphics Library in C.

It stores some color codes of pixels in memory (called canvas here) and you are free to use this pixels wherever you want. You can write the pixels to `.ppm` file or build `.c` code to `.wasm` and display the pixels on JavaScript Canvas. Keep reading to see examples on both platforms.

Visit [Playground](https://orhanemree.github.io/aldrin/) to try online.

Visit [Editor](https://orhanemree.github.io/aldrin/editor.html) to try online editor project made with Aldrin.

## Quick Start
* Just copy and paste `/src/aldrin.c` file to your project.
```c
#include "aldrin.c" // that's it!
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
Output should look something like this:

<img src="img/hello_world.png">

Note that: `aldrin_save_ppm()` function generates `.ppm` output (see [`/img/hello_world.ppm`](img/hello_world.ppm)). The output converted to `.png` format to be displayed here.

## Build
* Build to normal `C` program.
```bash
$ clang -DPLATFORM_C -o <filename> <filename>.c
# or
$ gcc <filename>.c -o <filename> -DPLATFORM_C
```

* Build to `.wasm` platform.
```bash
$ clang -DPLATFORM_WASM --target=wasm32 -o <filename>.o -c <filename>.c
$ wasm-ld --no-entry --allow-undefined --export-all -o <filename>.wasm <filename>.o
```
* Note: Make sure you have `clang` and `wasm-ld` installed.

## Examples
* See [`/examples`](examples).

## Running Tests
* You need Python to run tests.
```bash
$ cd test
$ python main.py
```
* Get more info:
```bash
$ python main.py help
```

## Documentation
* See [`docs/DOCUMENTATION.md`](docs/DOCUMENTATION.md) to read from file.
* See [`website`](https://orhanemree.github.io/aldrin/reference.html) to read from web and run examples live.

## References
* [Gabriel Gambetta / Computer Graphics from Scratch](https://gabrielgambetta.com/computer-graphics-from-scratch/)
* [Tsoding / Graphics Library in C [Video]](https://youtu.be/LmQKZmQh1ZQ)
* ChatGPT of course :D

## License
* Licensed under the [MIT License](LICENSE).