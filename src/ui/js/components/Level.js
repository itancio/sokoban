import Menu from "./Menu.js";
import storage from "../storage.js";
import soko from "../soko.js";


/**
 * Renders and handles events associated with playing a level
*/
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

  /**
   * This function renders 
   * @param HTMLElement root the root element to render into
   * @param number levelNumber the level to play
  */
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

    /**
     * Maps a row to its HTML string
     * @param string[] row the row to render
     * @param number rowIndex the index of the row
     * @return string the row
    */
    const buildRowHTML = (row, rowIndex) => `
      <tr>
        ${row.map((cell, i) => `
            <td
              data-row="${rowIndex}"
              data-col="${i}"
              class="cell ${this.cellToClass[cell] || ""}"
            ></td>
          `)
          .join("")}
      </tr>
    `;

    let outsideTiles = null;

    /**
     * This function detects which floor tiles are outside of the walls.
     * Mutates outsideTiles for performance purposes.
     * @param string[] board the board to detect tiles on
    */
    const detectOutsideTiles = board => {
      const flood = (board, row, col) => {
        if (board[row] && board[row][col] === " ") {
          board[row][col] = "_";
          outsideTiles.push([row, col]);
          flood(board, row - 1, col);
          flood(board, row + 1, col);
          flood(board, row, col - 1);
          flood(board, row, col + 1);
        }
      };

      outsideTiles = [];

      // left edge
      for (let i = 0; i < board.length; i++) {
        flood(board, i, 0);
      }

      // top edge
      for (let i = 0; i < board[0].length; i++) {
        flood(board, 0, i);
      }

      // bottom edge
      for (let i = 0; i < board.at(-1).length; i++) {
        flood(board, board.length - 1, i);
      }

      // right edge
      for (let i = 0; i < board.length; i++) {
        flood(board, i, board[i].length - 1);
      }
    };

    /**
     * Renders the current Sokoban game board to the DOM
    */
    const renderBoard = () => {
      const board = soko.boardToStr().split("\n").map(e => [...e]);
      const longestRow = Math.max(...board.map(e => e.length));

      for (const row of board) {
        row.push(..." ".repeat(longestRow - row.length));
      }

      if (outsideTiles) {
        for (const [row, col] of outsideTiles) {
          board[row][col] = "_";
        }
      }
      else {
        detectOutsideTiles(board);
      }

      boardEl.innerHTML = `
        <table><tbody>
          ${board.map(buildRowHTML).join("")}
        </tbody></table>
      `;
    };

    /**
     * Renders the status bar showing information about the game to the player
    */
    const renderStatusBar = () => {
      statusEl.innerHTML = `
        <div>Moves: ${soko.sequence().length}</div>
      `;
    };

    /**
     * Perform a full rerender of the game board, including status bar
    */
    const render = () => {
      renderBoard();
      renderStatusBar();
      undoEl.disabled = resetEl.disabled = soko.sequence().length === 0;

      if (document.activeElement) {
        document.activeElement.blur();
      }
    };

    // Converts event.code to a Sokoban Direction string
    const moves = {
      KeyA: "L",
      ArrowLeft: "L",
      KeyW: "U",
      ArrowUp: "U",
      KeyD: "R",
      ArrowRight: "R",
      KeyS: "D",
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

    /**
     * Handler for level completion, displaying a 
     * victory message and saving the best score
    */
    const handleLevelCompleted = () => {
      statusEl.textContent = `Solved in ${soko.sequence().length} moves`;
      storage.saveBestScore(levelNumber, soko.sequence().length);
    };

    /**
     * Handler for mouse click events on the board, triggering a long move
    */
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

    /**
     * Handler for click events on the undo button
    */
    undoEl.addEventListener("click", event => {
      if (soko.undo()) {
        render();
      }
    });

    /**
     * Handler for click events on the reset button
    */
    resetEl.addEventListener("click", event => {
      soko.reset();
      render();
    });

    render();
  }
};

export default Level;
