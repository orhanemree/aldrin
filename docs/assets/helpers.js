export const make_environment = (...envs) => {
    return new Proxy(envs, {
        get(target, prop, receiver) {
            for (let env of envs) {
                if (env.hasOwnProperty(prop)) {
                    return env[prop];
                }
            }
            return (...args) => { console.error("NOT IMPLEMENTED: " + prop, args) }
        }
    });
}


export const loadWasm = async filepath => {
    const wasm = await WebAssembly.instantiateStreaming(fetch(filepath), {
        env: make_environment(),
    });

    return wasm.instance.exports;
}


export const displayPixels = (canvas, width, height, pixels) => {
    canvas.width = width;
    canvas.height = height;
    const ctx = canvas.getContext("2d", { willReadFrequently: true });
    
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    ctx.fillStyle = "white";
    ctx.fillRect(0, 0, canvas.width, canvas.height);

    const imageData = ctx.getImageData(0, 0, canvas.width, canvas.height);
    const imagePixels = imageData.data;

    for (let i = 0; i < imagePixels.length; i += 4) {
        /* c and javascript, store data different
            when we input 0xff00ff00 in js side
            it returns 0x00ff00ff in c side
            so we need to reverse color codes here */
            imagePixels[i] = pixels[i + 2]     // r
            imagePixels[i + 1] = pixels[i + 1] // g
            imagePixels[i + 2] = pixels[i]     // b 
            imagePixels[i + 3] = 255           // a
    }

    ctx.putImageData(imageData, 0, 0);
}


export const runProgram = (exports, canvas, program) => {
    const ac = exports.ac;
    const width = exports.aldrin_get_width(ac);
    const height = exports.aldrin_get_height(ac);
    // multiply by 4 because R, G, B, A are separately 8 bites
    const pixels =  new Uint8Array(exports.memory.buffer, exports.aldrin_get_pixels(ac), width*height*4);

    // clear canvas first
    exports["aldrin_fill"](exports.ac, 0x000000);

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
            // arg is a string
            if (a[0] === a[a.length-1] && a[0] === "\"") {
                /*
                we can't pass string values as argument from js to wasm
                to do this we need to encode string first
                then allocate wasm memory (make sure it is empty)
                then write chars of string to the reserved memory separately
                and pass pointer of reserved memory as argument

                implementation:
                */
                // encode text
                const encoder = new TextEncoder();
                const encoded = encoder.encode(a.substring(1, a.length-1));
                const pointer = exports.aldrin_get_pixels(ac)+width*height*4;
                // allocate wasm memory to store text
                const memoryToStore = new Uint8Array(exports.memory.buffer, pointer, encoded.length);
                // store char of string separately
                for (let i = 0; i < encoded.length; ++i) {
                    memoryToStore[i] = encoded[i];
                }
                // return pointer of string
                return pointer;
            }
            // args is something else
            return a;
        });

        // run function
        console.log(`[INFO] running func ${func.trim()}()\nwith parameters ${args}`);
        exports[func.trim()](...args);
        
        // display output on canvas
        displayPixels(canvas, width, height, pixels);
    }
}
