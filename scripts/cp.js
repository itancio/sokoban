const fs = require("fs").promises;
const path = require("path");

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

module.exports = cp;
