import { loadWasm, runProgram, saveCanvas } from "./helpers.js";

const WASM_PATH = "wasm/main.wasm";
const MIN_THICKNESS = 1;
const MIN_TEXT_SIZE = 1;

const canvas = document.querySelector("canvas#c");
const toolButtons = document.querySelectorAll("button");
const inputs = document.querySelectorAll("input");
const drawIcon = document.querySelector("svg#draw");
const fillIcon = document.querySelector("svg#fill");
const downloadImg = document.querySelector("button#download-img");

let exports, startX, startY, text = "", code = "", program = "", undone = "",
    tx, ty, tGot = 0; /* triangle points see if (tool === "triangle") */

// default values for functions
let tool = "line",
    drawing = false,
    color = 0xffffff,
    thickness = 1,
    textSize = 1,
    mode = "draw";


const undo = () => {
    if (program) {
        const splitted = program.split("\n");
        program = splitted.slice(0, splitted.length-2).join("\n");
        undone += splitted.slice(splitted.length-2, splitted.length-1).join("\n") + "\n";
        
        if (program) {
            program += "\n"
            runProgram(exports, canvas, program, 1, 0);
        } else {
            // clear canvas
            runProgram(exports, canvas, "aldrin_fill(ac, 0x000000)", 1, 0);
        }
    }
}


const redo = () => {
    if (undone) {
        const splitted = undone.split("\n");
        undone = splitted.slice(0, splitted.length-2).join("\n");
        program += splitted.slice(splitted.length-2, splitted.length-1).join("\n") + "\n";
    
        if (undone) {
            undone += "\n";
        }

        runProgram(exports, canvas, program, 1, 0);
    }
}


const toggleMode = () => {
    if (mode === "draw") {
        mode = "fill";
        drawIcon.style.display = "none";
        fillIcon.style.display = "block";

    } else if (mode === "fill") {
        mode = "draw";
        fillIcon.style.display = "none";
        drawIcon.style.display = "block";
    }
}


toolButtons.forEach(b => {
    b.onclick = () => {
        if (!drawing) {
            if (b.id === "mode") {
                toggleMode();
            }
            else if (b.id === "undo") undo();
            else if (b.id === "redo") redo();
            else {
                tool = b.id;
                toolButtons.forEach(tb => tb.classList.remove("active"));
                b.classList.add("active");
            }
        }
    }
});


inputs.forEach(i => {
    i.onchange = () => {
        if (!drawing) {
            if (i.id === "color") {
                color = +i.value.replace("#", "0x");
            } else if (i.id === "thickness") {
                thickness = Math.max(+i.value, MIN_THICKNESS);
            } else if (i.id === "text-size") {
                textSize = Math.max(+i.value, MIN_TEXT_SIZE);
            }
        }
    }
});


canvas.onclick = e => {
    if (drawing) {
        if (tool === "triangle") {
            if (tGot === 1) {
                tGot = 2;
                return;
            }
            if (tGot === 2) tGot = 0;
        }
        program += code;
        drawing = false;
        code = "";
        text = "";
        
    } else {
        const bbox = e.target.getBoundingClientRect();
        startX = e.x - bbox.left;
        startY = e.y - bbox.top;

        // clicked for the first point of triangle
        if (tool === "triangle") {
            tGot = 1;
        }

        drawing = true;
    }
}


canvas.onmousemove = e => {
    if (drawing) {
        const bbox = e.target.getBoundingClientRect();

        if (tool === "line") {
            code = `aldrin_draw_line(ac, \
                ${startX}, ${startY}, ${e.x - bbox.left}, ${e.y - bbox.top}, ${color}, ${thickness});\n`;
        }

        else if (tool === "ellipse") {

            const rx = startX - (e.x-bbox.left);
            const ry = startY - (e.y-bbox.top);

            if (mode === "draw") {
                code = `aldrin_draw_ellipse(ac, \
                    ${rx < 0 ? startX : startX-rx}, ${ry < 0 ? startY : startY-ry}, \
                    ${Math.abs(rx)/2}, ${Math.abs(ry)/2}, ${color});\n`;

            } else if (mode === "fill") {
                code = `aldrin_fill_ellipse(ac, \
                    ${rx < 0 ? startX : startX-rx}, ${ry < 0 ? startY : startY-ry}, \
                    ${Math.abs(rx)/2}, ${Math.abs(ry)/2}, ${color});\n`;
            }
        } 
        
        else if (tool === "triangle") {

            if (mode === "draw") {

                if (tGot === 1) {
                    // positioning second point of triangle
                    tx = e.x-bbox.left;
                    ty = e.y-bbox.top;
                    code = `aldrin_draw_triangle(ac, \
                        ${startX}, ${startY}, ${tx}, ${ty}, \
                        ${tx}, ${ty}, ${color}, ${thickness});\n`;

                } else if (tGot === 2) {
                    // positioning third point of triangle
                    code = `aldrin_draw_triangle(ac, \
                        ${startX}, ${startY}, ${tx}, ${ty}, \
                        ${e.x-bbox.left}, ${e.y-bbox.top}, \
                        ${color}, ${thickness});\n`;
                }

            } else if (mode === "fill") {

                if (tGot === 1) {
                    // positioning second point of triangle
                    tx = e.x-bbox.left;
                    ty = e.y-bbox.top;
                    code = `aldrin_fill_triangle(ac, \
                        ${startX}, ${startY}, ${tx}, ${ty}, \
                        ${tx}, ${ty}, ${color});\n`;

                } else if (tGot === 2) {
                    // positioning third point of triangle
                    code = `aldrin_fill_triangle(ac, \
                        ${startX}, ${startY}, ${tx}, ${ty}, \
                        ${e.x-bbox.left}, ${e.y-bbox.top}, \
                        ${color});\n`;
                }
            }

        } 
        
        else if (tool === "rectangle") {

            const w = startX - (e.x-bbox.left);
            const h = startY - (e.y-bbox.top);

            if (mode === "draw") {
                code = `aldrin_draw_rectangle(ac, \
                    ${w < 0 ? startX : startX-w}, ${h < 0 ? startY : startY-h}, \
                    ${Math.abs(w)}, ${Math.abs(h)}, ${color}, ${thickness});\n`;

            } else if (mode === "fill") {
                code = `aldrin_fill_rectangle(ac, \
                    ${w < 0 ? startX : startX-w}, ${h < 0 ? startY : startY-h}, \
                    ${Math.abs(w)}, ${Math.abs(h)}, ${color});\n`;
            }
        }

        else if (tool === "text") {
            // see canvas.onkeydown function
            return;
        }
        
        else {
            return;
        }

        runProgram(exports, canvas, program, 1, 0);
        runProgram(exports, canvas, code, 0, 0);
    }
}


canvas.onkeydown = e => {
    if (drawing) {
        // use aldrin_text()
        if (tool === "text") {
            if (e.key.length === 1) {
                // normal chars like a, 0, and space
                text += e.key;

            } else if (e.key === "Backspace") {
                // delete last char of text
                text = text.substring(0, text.length-1);
                    
            } else {
                console.log(`[WARN]: key ${e.key} not implemented.`);
                return;
            }

            code = `aldrin_text(ac, \
                ${startX}, ${startY}, "${text}", ${color}, ${textSize});\n`;

            runProgram(exports, canvas, program, 1, 0);
            runProgram(exports, canvas, code, 0, 0);
        }
    }
}


/*
--- shortcuts ---
CTRL+Z:  undo
CTRL+Y:  redo 
L:       line tool
E:       ellipse tool
T:       text tool
R:       rectangle tool
ALT+T:  text tool
CTRL+M:  toggle mode
*/

window.onkeydown = e => {
    if (!drawing) {
        if (e.ctrlKey && e.key === "z") {
            undo();
        }
        
        else if (e.ctrlKey && e.key === "y") {
            redo();
        }

        else if (e.ctrlKey && e.key === "m") {
            toggleMode();
        }

        else if (e.altKey && e.key === "t") {
            tool = "text";
        }

        else if (e.key === "l") {
            tool = "line";
        }

        else if (e.key === "e") {
            tool = "ellipse";
        }

        else if (e.key === "t") {
            tool = "triangle";
        }

        else if (e.key === "r") {
            tool = "rectangle";
        }
    }
}


window.onload = async () => {
    // initialize wasm
    exports = await loadWasm(WASM_PATH);
    runProgram(exports, canvas, "aldrin_fill(ac, 0x000000)", 1, 0);
}


// download canvas as .png file
downloadImg.onclick = () => {
    saveCanvas(canvas, "aldrin-editor.png");
}
