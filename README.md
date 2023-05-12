<p align="center">
    <img src="img/lily_aldrin.png">
</p>

# 👩‍🦰 Aldrin
Simple 2D Computer Graphics Library in C.

It stores some color codes of pixels in memory (called canvas here) and you are free to use this pixels wherever you want. You can write the pixels to `.ppm` file or build `.c` code to `.wasm` and display the pixels on JavaScript Canvas. Keep reading to see examples on both paltforms.

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
Output should look something like:

<img src="img/hello_world.png">

Note that: `aldrin_save_ppm()` function generates `.ppm` output (see [`/img/hello_world.ppm`](img/hello_world.ppm)). The output converted to `.png` format to be displayed here.

## Build
### Platform=C
* Generates executable output.
```bash
$ bash build.sh <EXTENSION_LESS_FILENAME>
# or
$ bash build.sh c <EXTENSION_LESS_FILENAME>
```
* For example this code builds `main.c` to `main` executable:
```bash
$ bash build.sh main
```

### Platform=WASM
* Generates `.wasm` output.
```bash
$ bash build.sh wasm <EXTENSION_LESS_FILENAME>
```
* For example this code builds `main.c` to `main.wasm`:
```bash
$ bash build.sh wasm main
```

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

## Examples
* See [`/examples`](examples).

## Documentation
* See [`DOCUMENTATION.md`](DOCUMENTATION.md).

## References
* [Gabriel Gambetta / Computer Graphics from Scratch](https://gabrielgambetta.com/computer-graphics-from-scratch/)
* [Tsoding / Graphics Library in C [Video]](https://youtu.be/LmQKZmQh1ZQ)
* ChatGPT of course :D

## License
* Licensed under the [MIT License](LICENSE).