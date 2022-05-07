import Menu from "./Menu.js";
import storage from "../storage.js";
import soko from "../soko.js";


const Level = {
  html: `
    <div id="game">
      <div id="controls">
        <button title="Undo (z)" id="undo" disabled>
          <span class="material-symbols-outlined">undo</span>
        </button>
        <button title="Reset (r)" id="reset">
          <span class="material-symbols-outlined">refresh</span>
        </button>
        <button title="Change Level" id="change-level">
          <span class="material-symbols-outlined">home</span>
        </button>
      </div>
      <div id="board"></div>
      <div id="status"></div>
    </div>
  `,

  cellToClass: {
    "_": "floor-outside",
    " ": "floor",
    "#": "wall",
    "@": "player",
    "+": "player-on-goal",
    "$": "box",
    "*": "box-on-goal",
    ".": "goal",
  },

  render(root, levelNumber) {
    root.innerHTML = this.html;
    document
      .querySelector("#change-level")
      .addEventListener("click", () => {
        location.hash = "";
        Menu.render(root);
      })
    ;

    if (levelNumber < 0 || levelNumber > soko.levelsSize()) {
      location.hash = "";
      return;
    }

    soko.changeLevel(levelNumber);

    const boardEl = document.getElementById("board");
    const undoEl = document.getElementById("undo");
    const resetEl = document.getElementById("reset");
    const statusEl = document.querySelector("#status");
    const buildRowHTML = (row, rowIndex) => `
      <tr>
        ${[...row.replace(/(?:^ +)|(?: +$)/g, m => "_".repeat(m.length))]
          .map((cell, i) => `
            <td
              data-row="${rowIndex}"
              data-col="${i}"
              class="cell ${this.cellToClass[cell] || ""}"
            ></td>
          `)
          .join("")}
      </tr>
    `;
    const renderBoard = () => {
      boardEl.innerHTML =
        "<table><tbody>" +
          soko.boardToStr()
            .split("\n")
            .map(buildRowHTML)
            .join("") +
        "</tbody></table>"
      ;
    };

    const renderStatusBar = () => {
      statusEl.innerHTML = `
        <div>Moves: ${soko.sequence().length}</div>
      `;
    };

    const render = () => {
      renderBoard();
      renderStatusBar();
  
      undoEl.disabled = resetEl.disabled =
        soko.sequence().length === 0
      ;
    };

    const moves = {
      ArrowLeft: "L",
      ArrowUp: "U",
      ArrowRight: "R",
      ArrowDown: "D",
    };
    document.onkeydown = event => {
      if (event.code in moves) {
        if (soko.solved()) {
          return;
        }

        event.preventDefault();

        if (soko.move(moves[event.code])) {
          render();

          if (soko.solved()) {
            handleLevelCompleted();
          }
        }
      }
      else if (event.code === "KeyZ" && soko.undo()) {
        render();
      }
      else if (event.code === "KeyR") {
        soko.reset();
        render();
      }
    };

    const handleLevelCompleted = () => {
      statusEl.textContent = `Solved in ${soko.sequence().length} moves`;
      storage.saveBestScore(levelNumber, soko.sequence().length);
      undoEl.disabled = true;
    };

    boardEl.addEventListener("click", event => {
      const cell = event.target.closest("td");

      if (soko.solved() || !cell || !boardEl.contains(cell)) {
        return;
      }
 
      const row = +cell.getAttribute("data-row");
      const col = +cell.getAttribute("data-col");
 
      if (soko.goto(row, col)) {
        render();

        if (soko.solved()) {
          handleLevelCompleted();
        }
      }
    });

    undoEl.addEventListener("click", event => {
      if (soko.undo()) {
        render();
      }
    });
    resetEl.addEventListener("click", event => {
      soko.reset();
      render();
    });

    render();
  }
};

export default Level;
