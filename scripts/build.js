const fs = require("fs").promises;
const path = require("path");
const {exec} = require("child_process");
const cp = require("./cp");

const emcc = `
  emcc src/engine/main.cpp src/engine/sokoban.cpp
  -std=c++1z
  -o dist/sokoban.js 
  -s NO_EXIT_RUNTIME=1
  -s LINKABLE=1
  -s EXPORT_ALL=1
  -s "EXPORTED_RUNTIME_METHODS=['ccall', 'cwrap']"
  --preload-file "src/engine/levels"
`.replace(/\n/g, " ");

const src = path.join("src", "ui");
const dist = "dist";

(async () => {
  await fs.mkdir(dist).catch(err => {});
  exec(emcc, async (err, stdout, stderr) => {
    if (err) {
      console.error(err.message);
      process.exit(1);
    }

    if (stdout) {
      console.log(stdout);
    }

    if (stderr) {
      console.log(stderr);
    }

    await cp(src, dist);
  });
})();

