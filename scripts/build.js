const fs = require("fs").promises;
const path = require("path");
const {exec} = require("child_process");

const emcc = `
  emcc src/main.cpp src/sokoban.cpp
  -std=c++1z
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
      if (/\.(?:js|css|html)$/.test(f) || f === "assets") {
        await cp(path.join(src, f), path.join(dist, f));
      }
    }
  });
})();

const cp = async (src, dest) => {
  const lstat = await fs.lstat(src).catch(err => false);

  if (!lstat) {
    return;
  }
  else if (await lstat.isFile()) {
    await fs.copyFile(src, dest);
  }
  else if (await lstat.isDirectory()) {
    await fs.mkdir(dest).catch(err => {});

    for (const f of await fs.readdir(src)) {
      await cp(path.join(src, f), path.join(dest, f));
    }
  }
};

