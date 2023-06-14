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
