# 👩‍🦰 Aldrin Documentation

<details>
  <summary>Table of Contents</summary>

- [👩‍🦰 Aldrin Documentation](#-aldrin-documentation)
  - [API Reference](#api-reference)
    - [`Aldrin_Canvas`](#aldrin_canvas)
    - [`aldrin_put_pixel()`](#aldrin_put_pixel)
    - [`aldrin_fill()`](#aldrin_fill)
    - [`aldrin_draw_line()`](#aldrin_draw_line)
    - [`aldrin_draw_triangle()`](#aldrin_draw_triangle)
    - [`aldrin_fill_triangle()`](#aldrin_fill_triangle)
    - [`aldrin_draw_ellipse()`](#aldrin_draw_ellipse)
    - [`aldrin_fill_ellipse()`](#aldrin_fill_ellipse)
    - [`aldrin_draw_circle()`](#aldrin_draw_circle)
    - [`aldrin_fill_circle()`](#aldrin_fill_circle)
    - [`aldrin_draw_rectangle()`](#aldrin_draw_rectangle)
    - [`aldrin_fill_rectangle()`](#aldrin_fill_rectangle)
    - [`aldrin_draw_square()`](#aldrin_draw_square)
    - [`aldrin_fill_square()`](#aldrin_fill_square)
    - [`aldrin_get_pixels()`](#aldrin_get_pixels)
    - [`aldrin_get_width()`](#aldrin_get_width)
    - [`aldrin_get_height()`](#aldrin_get_height)
    - [`aldrin_save_ppm()`](#aldrin_save_ppm)
</details>

## API Reference

### `Aldrin_Canvas`
* Main data type of Aldrin that contains `pixels`, `width` and `height` properties of canvas.
* Example:
```c
#define WIDTH 200
#define HEIGHT 200

static uint32_t pixels[WIDTH*HEIGHT];

Aldrin_Canvas ac = { pixels, WIDTH, HEIGHT };
```

### `aldrin_put_pixel()`
* Puts a pixel on the canvas.
* Syntax: aldrin_put_pixel(ac, x, y, color)
* Parameters:
  - `ac`: `Aldrin_Canvas`
  - `x`: `uint32_t`: x coordinate of pixel
  - `y`: `uint32_t`: y coordinate of pixel
  - `color`: `uint32_t`: color code of pixel
* Example: 
```c
aldrin_put_pixel(ac, 100, 100, 0x00ff00);
```
* [See live output](https://orhanemree.github.io/aldrin/reference.html?r=aldrin_put_pixel).

### `aldrin_fill()`
* Fills canvas with color.
* Syntax: aldrin_fill(ac, fill_color)
* Parameters:
  - `ac`: `Aldrin_Canvas`
  - `fill_color`: `uint32_t`: color code of fill
* Example: 
```c
aldrin_fill(ac, 0x00ff00);
```
* [See live output](https://orhanemree.github.io/aldrin/reference.html?r=aldrin_fill).

### `aldrin_draw_line()`
* Draws a line on the canvas.
* Syntax: aldrin_draw_line(ac, x1, y1, x2, y2, line_color, thickness)
* Parameters:
  - `ac`: `Aldrin_Canvas`
  - `x1`: `uint32_t`: x coordinate of first point
  - `y1`: `uint32_t`: y coordinate of first point
  - `x2`: `uint32_t`: x coordinate of second point
  - `y2`: `uint32_t`: y coordinate of second point
  - `line_color`: `uint32_t`: color code of line
  - `thickness`: "uint32_t`: thickness of line
* Example: 
```c
aldrin_draw_line(ac, 0, 0, 200, 200, 0xff0000, 5);
```
* [See live output](https://orhanemree.github.io/aldrin/reference.html?r=aldrin_draw_line).

### `aldrin_draw_triangle()`
* Draws a triangle on the canvas.
* Syntax: aldrin_draw_triangle(ac, x1, y1, x2, y2, x3, y3, line_color, thickness)
* Parameters:
  - `ac`: `Aldrin_Canvas`
  - `x1`: `uint32_t`: x coordinate of first point
  - `y1`: `uint32_t`: y coordinate of first point
  - `x2`: `uint32_t`: x coordinate of second point
  - `y2`: `uint32_t`: y coordinate of second point
  - `x3`: `uint32_t`: x coordinate of third point
  - `y3`: `uint32_t`: y coordinate of third point
  - `line_color`: `uint32_t`: color code of line
  - `thickness`: "uint32_t`: thickness of line
* Example: 
```c
aldrin_draw_triangle(ac, 5, 10, 5, 100, 120, 10, 0xff0000, 1);
```
* [See live output](https://orhanemree.github.io/aldrin/reference.html?r=aldrin_draw_triangle).

### `aldrin_fill_triangle()`
* Draws and fills a triangle on the canvas.
* Syntax: aldrin_fill_triangle(ac, x1, y1, x2, y2, x3, y3, fill_color)
* Parameters:
  - `ac`: `Aldrin_Canvas`
  - `x1`: `uint32_t`: x coordinate of first point
  - `y1`: `uint32_t`: y coordinate of first point
  - `x2`: `uint32_t`: x coordinate of second point
  - `y2`: `uint32_t`: y coordinate of second point
  - `x3`: `uint32_t`: x coordinate of third point
  - `y3`: `uint32_t`: y coordinate of third point
  - `fill_color`: `uint32_t`: color code of fill
* Example: 
```c
aldrin_fill_triangle(ac, 5, 10, 5, 100, 120, 10, 0xff0000);
```
* [See live output](https://orhanemree.github.io/aldrin/reference.html?r=aldrin_fill_triangle).

### `aldrin_draw_ellipse()`
* Draws a ellipse on the canvas.
* Syntax: aldrin_draw_ellipse(ac, x, y, rx, ry, line_color)
* Parameters:
  - `ac`: `Aldrin_Canvas`
  - `x`: `uint32_t`: x coordinate of center of ellipse
  - `y`: `uint32_t`: y coordinate of center of ellipse
  - `rx`: `uint32_t`: x radius of ellipse
  - `ry`: `uint32_t`: y radius of ellipse
  - `line_color`: `uint32_t`: color code of line
* Example: 
```c
aldrin_draw_ellipse(ac, 0, 0, 90, 50, 0xff0000);
```
* [See live output](https://orhanemree.github.io/aldrin/reference.html?r=aldrin_draw_ellipse).

### `aldrin_fill_ellipse()`
* Draws and fills a ellipse on the canvas.
* Syntax: aldrin_fill_ellipse(ac, x, y, rx, ry, fill_color)
* Parameters:
  - `ac`: `Aldrin_Canvas`
  - `x`: `uint32_t`: x coordinate of center of ellipse
  - `y`: `uint32_t`: y coordinate of center of ellipse
  - `rx`: `uint32_t`: x radius of ellipse
  - `ry`: `uint32_t`: y radius of ellipse
  - `fill_color`: `uint32_t`: color code of fill
* Example: 
```c
aldrin_fill_ellipse(ac, 0, 0, 90, 50, 0xff0000);
```
* [See live output](https://orhanemree.github.io/aldrin/reference.html?r=aldrin_fill_ellipse).

### `aldrin_draw_circle()`
* Draws a circle on the canvas.
* Syntax: aldrin_draw_circle(ac, x, y, r, line_color)
* Parameters:
  - `ac`: `Aldrin_Canvas`
  - `x`: `uint32_t`: x coordinate of center of circle
  - `y`: `uint32_t`: y coordinate of center of circle
  - `r`: `uint32_t`: radius of circle
  - `line_color`: `uint32_t`: color code of line
* Example: 
```c
aldrin_draw_circle(ac, 0, 0, 50, 0xff0000);
```
* [See live output](https://orhanemree.github.io/aldrin/reference.html?r=aldrin_draw_circle).

### `aldrin_fill_circle()`
* Draws and fills a circle on the canvas.
* Syntax: aldrin_fill_circle(ac, x, y, r, fill_color)
* Parameters:
  - `ac`: `Aldrin_Canvas`
  - `x`: `uint32_t`: x coordinate of center of circle
  - `y`: `uint32_t`: y coordinate of center of circle
  - `r`: `uint32_t`: radius of circle
  - `fill_color`: `uint32_t`: color code of fill
* Example: 
```c
aldrin_fill_circle(ac, 0, 0, 50, 0xff0000);
```
* [See live output](https://orhanemree.github.io/aldrin/reference.html?r=aldrin_fill_circle).

### `aldrin_draw_rectangle()`
* Draws a rectangle on the canvas.
* Syntax: aldrin_draw_rectangle(ac, x, y, w, h, line_color, thickness)
* Parameters:
  - `ac`: `Aldrin_Canvas`
  - `x`: `uint32_t`: x coordinate of center of rectangle
  - `y`: `uint32_t`: y coordinate of center of rectangle
  - `w`: `uint32_t`: width of rectangle
  - `h`: `uint32_t`: height of rectangle
  - `line_color`: `uint32_t`: color code of line
  - `thickness`: "uint32_t`: thickness of line
* Example: 
```c
aldrin_draw_rectangle(ac, 0, 0, 200, 100, 0x0000ff, 1);
```
* [See live output](https://orhanemree.github.io/aldrin/reference.html?r=aldrin_draw_rectangle).

### `aldrin_fill_rectangle()`
* Draws and fills a rectangle on the canvas.
* Syntax: aldrin_fill_rectangle(ac, x, y, w, h, line_color, thickness)
* Parameters:
  - `ac`: `Aldrin_Canvas`
  - `x`: `uint32_t`: x coordinate of center of rectangle
  - `y`: `uint32_t`: y coordinate of center of rectangle
  - `w`: `uint32_t`: width of rectangle
  - `h`: `uint32_t`: height of rectangle
  - `fill_color`: `uint32_t`: color code of fill
* Example: 
```c
aldrin_fill_rectangle(ac, 0, 0, 200, 100, 0x0000ff);
```
* [See live output](https://orhanemree.github.io/aldrin/reference.html?r=aldrin_fill_rectangle).

### `aldrin_draw_square()`
* Draws a square on the canvas.
* Syntax: aldrin_draw_square(ac, x, y, l, line_color, thickness)
* Parameters:
  - `ac`: `Aldrin_Canvas`
  - `x`: `uint32_t`: x coordinate of center of rectangle
  - `y`: `uint32_t`: y coordinate of center of rectangle
  - `l`: `uint32_t`: lenght (width and height) of rectangle
  - `line_color`: `uint32_t`: color code of line
* Example: 
```c
aldrin_draw_square(ac, 0, 0, 100, 0x0000ff, 1);
```
* [See live output](https://orhanemree.github.io/aldrin/reference.html?r=aldrin_draw_square).

### `aldrin_fill_square()`
* Draws and fills a square on the canvas.
* Syntax: aldrin_fill_square(ac, x, y, l, fill_color)
* Parameters:
  - `ac`: `Aldrin_Canvas`
  - `x`: `uint32_t`: x coordinate of center of rectangle
  - `y`: `uint32_t`: y coordinate of center of rectangle
  - `l`: `uint32_t`: lenght (width and height) of rectangle
  - `fill_color`: `uint32_t`: color code of fill
* Example: 
```c
aldrin_fill_square(ac, 0, 0, 100, 0x0000ff);
```
* [See live output](https://orhanemree.github.io/aldrin/reference.html?r=aldrin_fill_square).

### `aldrin_get_pixels()`
* Returns the pixels of the `Aldrin_Canvas`.
* Syntax: aldrin_get_pixels(ac)
* Parameters:
  - `ac`: `Aldrin_Canvas`
* Note: This function makes sense with `WASM`.
* Example: 
```c
aldrin_get_pixels(ac);
```

### `aldrin_get_width()`
* Returns the width of the `Aldrin_Canvas`.
* Syntax: aldrin_get_width(ac)
* Parameters:
  - `ac`: `Aldrin_Canvas`
* Note: This function makes sense with `WASM`.
* Example: 
```c
aldrin_get_width(ac);
```

### `aldrin_get_height()`
* Returns the height of the `Aldrin_Canvas`.
* Syntax: aldrin_get_height(ac)
* Parameters:
  - `ac`: `Aldrin_Canvas`
* Note: This function makes sense with `WASM`.
* Example: 
```c
aldrin_get_height(ac);
```

### `aldrin_save_ppm()`
* Saves the `Aldrin_Canvas` as a ppm file.
* Syntax: aldrin_save_ppm(ac, filename)
* Parameters:
  - `ac`: `Aldrin_Canvas`
  - `filename`: `char[]`: filename of the ppm file
* ⚠ Note: This function is not available with `WASM`.
* Example: 
```c
aldrin_save_ppm(ac, "output.ppm");
```
