import { loadWasm, runProgram, saveCanvas } from "./helpers.js";

const WASM_PATH = "wasm/main.wasm";

const canvas = document.querySelector("canvas#c");
const textarea = document.querySelector("textarea#t");
const runBtn = document.querySelector("button#run");
const downloadCode = document.querySelector("button#download-code");
const downloadImg = document.querySelector("button#download-img");

let exports;


window.onload = async () => {
    exports = await loadWasm(WASM_PATH);
    runProgram(exports, canvas, textarea.value);
}


// run program with clicking button
runBtn.onclick = () => {
    runProgram(exports, canvas, textarea.value);
}


// run program with hitting CTRL+ENTER shortcut on textarea
textarea.onkeydown = e => {
    if (e.ctrlKey && e.key === "Enter") {
        e.preventDefault();
        runProgram(exports, canvas, textarea.value);
    }
}


// download code as .c file
downloadCode.onclick = () => {
    // genarate .c file from code
    const content = `
#include <stdint.h>
#include "src/aldrin.c"

#define WIDTH 200
#define HEIGHT 200

static uint32_t pixels[WIDTH*HEIGHT];

Aldrin_Canvas ac = { pixels, WIDTH, HEIGHT };

int main() {
    ${textarea.value}
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


// download canvas as .png file
downloadImg.onclick = () => {
    saveCanvas(canvas, "aldrin-playground.png");
}
