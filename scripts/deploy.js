const fs = require("fs").promises;
const path = require("path");
const cp = require("./cp");

const dist = "dist";
const docs = "docs";

(async () => {
  await fs.mkdir(docs).catch(err => {});
  await cp(dist, docs);
})();

