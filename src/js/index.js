import Level from "./components/Level.js";
import Loading from "./components/Loading.js";
import Menu from "./components/Menu.js";
import soko from "./soko.js";


const root = document.getElementById("app");
Loading.render(root);

moduleReady.then(() => {
  const handleRouting = () => {
    const level = +location.hash.replace(/^#/, "") - 1;
  
    if (level >= 0 && level < soko.levelsSize()) {
      Level.render(root, level);
    }
    else {
      location.hash = "";
      Menu.render(root);
    }
  };
  window.onhashchange = handleRouting;
  handleRouting();
});
