import { loadWasm, runProgram } from "./helpers.js";

const WASM_PATH = "wasm/main.wasm";
const REFERENCE_PATH = "DOCUMENTATION.md";
const PART_TO_LIVE = 14; // part count of live output

const canvas = document.querySelector("canvas#c");
const zeroMd = document.querySelector("zero-md");
const specDiv = document.querySelector("div#spec");
const specMd = document.querySelector("div#spec > zero-md > script");

const r = new URLSearchParams(window.location.search).get("r");

let exports;


window.onload = async () => {
    // initialize wasm
    exports = await loadWasm(WASM_PATH);

    // get documentation text
    const reference = await ((await fetch(REFERENCE_PATH)).text());
    const headers = reference.split("### `")
    .map(h => h.split("\r\n")[0].replace("()`", "")).filter((h, i) => i > 1 && i < PART_TO_LIVE+2)
    // ignore Aldrin_Canvas and other no visual functions

    if (r && headers.includes(r)) {
        // requested specific part of reference
        specDiv.style.display = "block";

        const part = reference.substring(reference.search("# `" + r), reference.length)
        .split("\r\n###")[0]

        const code = part.split("```c\r\n")[1].split("```")[0].trim();

        specMd.innerHTML = part + "* Live output: <br><br>";

        // run live example
        runProgram(exports, canvas, code);
    } else {
        zeroMd.style.display = "block";
    }

}
