import Level from "./components/Level.js";
import Loading from "./components/Loading.js";
import Menu from "./components/Menu.js";
import soko from "./soko.js";


// The root element for the entire single page app
const root = document.getElementById("app");
Loading.render(root);

moduleReady.then(() => {
  /**
   * Handler function for when routing changes, e.g. onhashchange and initial page load
  */
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
