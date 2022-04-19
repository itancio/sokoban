const onLoaded = () => {
  const loadingEl = document.getElementById("menu");
  const statusEl = document.getElementById("status");
  statusEl.innerHTML = "<button>start</button>";
  statusEl.querySelector("button").addEventListener("click", () => {
    const gameEl = document.getElementById("game");
    gameEl.classList.remove("hide");
    loadingEl.classList.add("hide");
    initializeGame();
  });
};

const initializeGame = () => {
  Module.ccall("sokoban_initialize");
  const soko = {
    levelNumber: Module.cwrap("sokoban_level"),
    move: Module.cwrap(
      "sokoban_move", // name of C function
      "bool",         // return type
      ["string"],     // argument types
    ),
    boardToStr: Module.cwrap(
      "sokoban_board_to_string",
      "string", // return type
    ),
    undo: Module.cwrap("sokoban_undo", "bool"),
    solved: Module.cwrap("sokoban_solved", "bool"),
  };

  const boardEl = document.getElementById("board");
  const undoEl = document.getElementById("undo");
  const cellToClass = {
    "_": "floor-outside",
    " ": "floor",
    "#": "wall",
    "@": "player",
    "+": "player-on-goal",
    "$": "box",
    "*": "box-on-goal",
    ".": "goal",
  };
  const buildRowHTML = (row, rowIndex) => `
    <tr>
      ${[...row.replace(/^ +/g, m => "_".repeat(m.length))]
        .map((cell, i) => `
          <td
            data-row="${rowIndex}"
            data-col="${i}"
            class="cell ${cellToClass[cell] || ""}"
          >
          </td>
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
  boardEl.addEventListener("click", event => {
    const cell = event.target.closest("td");

    if (!cell || !boardEl.contains(cell)) {
      return;
    }

    const row = +cell.getAttribute("data-row");
    const col = +cell.getAttribute("data-col");
    console.log(row, col);
  });
  undoEl.addEventListener("click", event => {
    if (soko.undo()) {
      renderBoard();
    }
  });
 
  const moves = {
    ArrowLeft: "L",
    ArrowUp: "U",
    ArrowRight: "R",
    ArrowDown: "D",
  };
  document.addEventListener("keydown", event => {
    if (event.code in moves) {
      event.preventDefault();

      if (soko.move(moves[event.code])) {
        //console.log(soko.boardToStr(), soko.levelNumber());
        renderBoard();

        if (soko.solved()) {
          console.log("solved!");
        }
      }
    }
    else if (event.code === "KeyZ" && soko.undo()) {
      renderBoard();
    }
  });

  renderBoard();
};

var Module = {
  preRun: [],
  postRun: [onLoaded],
  print: text => console.log(text),
  printErr: text => console.error(text),
};

