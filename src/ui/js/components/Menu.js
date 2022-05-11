import storage from "../storage.js";


/**
 * This interface represents the main landing title and level selection screen.
*/
const Menu = {
  render(root) {
    const menuHTML = `
    <div id="menu">
      <h1>Sokoban</h1>
      <div class="attribution">
        <em>by Irvin, Juan, Severin & Greg</em>
      </div>
      <ul>
        ${[...Array(Module.ccall("sokoban_levels_size"))].map((_, i) => `
          <li>
            <a href="#${i + 1}">
              <span class="material-symbols-outlined">
                ${storage.bestScore(i) === undefined ?
                  "check_box_outline_blank" : "check_box"}
              </span>
              <span>level ${i + 1}</span>
              <span>best: ${storage.bestScore(i) || "n/a"}</span>
            </a>
          </li>
        `).join("")}
      </ul>
    </div>
    `;
    root.innerHTML = menuHTML;
  }
};

export default Menu;
