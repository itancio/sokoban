const fs = require("fs").promises;
const path = require("path");

const dist = "dist";
const docs = "docs";

(async () => {
  await fs.mkdir(docs).catch(err => {});

  for (const f of await fs.readdir(dist)) {
    await fs.copyFile(path.join(dist, f), path.join(docs, f));
  }
})();
