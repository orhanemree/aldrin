import { loadWasm, displayPixels } from "./helpers.js";

const WASM_PATH = "wasm/main.wasm";

const canvas = document.querySelector("canvas#c");
const textarea = document.querySelector("textarea#t");
const runBtn = document.querySelector("button#run");
const downloadCode = document.querySelector("button#download-code");
const downloadImg = document.querySelector("button#download-img");

let exports, ac, width, height, pixels;


const runProgram = program => {
    // clear canvas first
    exports["aldrin_fill"](ac, 0x000000);

    // parse program
    const program_ = program.trim().replace(/\n/g, "");
    const lines = program_.split(");").filter(l => l !== "");

    for (const line of lines) {
        const [func, argsString] = line.split("(");

        const args = argsString.replace(")", "").split(", ")
        .filter(a => a !== "").map(a => {
            // arg is main Alrin_Canvas variable from wasm (c)
            if (a === "ac") return ac;
            // arg is a color
            if (a.startsWith("0x")) {
                // convert to color code
                return parseInt(a.replace("0x", ""), 16);
            }
            // arg is a number
            if (!isNaN(+a)) return +a;
            // args is string or something else
            return a;
        });

        // run function
        console.log(`[INFO] running func ${func.trim()}()\nwith parameters ${args}`);
        exports[func.trim()](...args);
        
        // display output on canvas
        displayPixels(canvas, width, height, pixels);
    }
}


window.onload = async () => {
    exports = await loadWasm(WASM_PATH);
    ac = exports.ac;
    width = exports.aldrin_get_width(ac);
    height = exports.aldrin_get_height(ac);
    // multiply by 4 because R, G, B, A are separately 8 bites
    pixels =  new Uint8Array(exports.memory.buffer, exports.aldrin_get_pixels(ac), width*height*4);
    console.log("[INFO] wasm initialized with properties:");
    console.log("[INFO] width:", width);
    console.log("[INFO] height:", height);

    runProgram(textarea.value);
}


// run program with clicking button
runBtn.onclick = () => {
    runProgram(textarea.value);
}


// run program with hitting CTRL+ENTER shortcut on textarea
textarea.onkeydown = e => {
    if (e.ctrlKey && e.key === "Enter") {
        e.preventDefault();
        runProgram(textarea.value);
    }
}


// download code as .c file
downloadCode.onclick = () => {
    // genarate .c file from code
    const content = `
#include <stdint.h>
#include "src/aldrin.c"

#define WIDTH ${width}
#define HEIGHT ${height}

static uint32_t pixels[WIDTH*HEIGHT];

Aldrin_Canvas ac = { pixels, WIDTH, HEIGHT };

int main() {
    ${textarea.value.replace(/\n/g, "\n\t")}
    return 0;
}
    `.trim();
    const fileURL = `data:application/octet-stream;charset=utf-8,${encodeURIComponent(content)}`;

    // download file
    const link = document.createElement("a");
    link.setAttribute("href", fileURL);
    link.setAttribute("download", "aldrin-playground.c");
    link.click();
    link.remove();
}


// download image as .png file
downloadImg.onclick = () => {
    // get canvas as png
    const imgURL = canvas.toDataURL();

    // download file
    const link = document.createElement("a");
    link.setAttribute("href", imgURL);
    link.setAttribute("download", "aldrin-playground.png");
    link.click();
    link.remove();
}