const fs = require("fs").promises;
const path = require("path");
const {exec} = require("child_process");

const emcc = `
  emcc src/main.cpp src/sokoban.cpp
  -o dist/sokoban.js 
  -s NO_EXIT_RUNTIME=1
  -s LINKABLE=1
  -s EXPORT_ALL=1
  -s "EXPORTED_RUNTIME_METHODS=['ccall', 'cwrap']"
`.replace(/\n/g, " ");
const src = "src";
const dist = "dist";

(async () => {
  await fs.mkdir(dist).catch(err => {});
  exec(emcc, async (err, stdout, stderr) => {
    if (err) {
      console.error(err.message);
      process.exit(1);
    }
    else if (stdout) {
      console.log(stdout);
    }
    else if (stderr) {
      console.log(stderr);
    }

    for (const f of await fs.readdir(src)) {
      if (/\.(?:js|html)$/.test(f)) {
        await fs.copyFile(path.join(src, f), path.join(dist, f));
      }
    }
  });
})();
