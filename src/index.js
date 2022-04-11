const initializeGame = () => {
  Module.ccall("sokoban_initialize");
  const soko = {
    levelNumber: Module.cwrap("sokoban_level"),
    move: Module.cwrap(
      "sokoban_move", // name of C function
      "bool",         // return type
      ["string"],     // argument types
    ),
    goTo: Module.cwrap(
      "sokoban_goTo",
      "bool",
      ["unsigned int",
      "unsigned int"]
    ),
    boardToStr: Module.cwrap(
      "sokoban_board_to_string",
      "string", // return type
    ),
    undo: Module.cwrap(
      "sokoban_undo",
      "bool", // return type
    ),
    redo: Module.cwrap(
      "sokoban_redo",
      "bool", // return type
    ),
  };

  const boardEl = document.getElementById("board");
  const undoEl = document.getElementById("undo");
  const redoEl = document.getElementById("redo");
  const cellToClass = {
    " ": "space",
    "#": "wall",
    "@": "player",
    "+": "player-on-goal",
    "$": "box",
    "*": "box-on-goal",
    ".": "goal",
  };
  const buildRowHTML = (row, rowIndex) => `
    <tr>
      ${[...row]
        .map((cell, i) => `
          <td
            data-row="${rowIndex}"
            data-col="${i}"
            class="cell ${cellToClass[cell] || ""}"
          >
            ${cell}
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

    if (soko.goTo(row, col)) {
      renderBoard();
    }
    console.log(row, col);
  });
  undoEl.addEventListener("click", event => {
    if (soko.undo()) {
      renderBoard();
    }
  });
  redoEl.addEventListener("click", event => {
    if (soko.redo()) {
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
      }
    }
  });

  renderBoard();
};

var Module = {
  preRun: [],
  postRun: [initializeGame],
  print: text => console.log(text),
  printErr: text => console.error(text),
};

