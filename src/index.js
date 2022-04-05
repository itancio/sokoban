const initializeGame = () => {
  const levelNumber = Module.cwrap("sokoban_level");
  const move = Module.cwrap(
    "sokoban_move", // name of C function
    "bool",         // return type
    ["string"],     // argument types
  );
  const boardToStr = Module.cwrap(
    "sokoban_board_to_string",
    "string", // return type
  );
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
        boardToStr()
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
 
  Module.ccall("sokoban_initialize");
  renderBoard();
  const moves = {
    ArrowLeft: "L",
    ArrowUp: "U",
    ArrowRight: "R",
    ArrowDown: "D",
  };

  document.addEventListener("keydown", event => {
    if (event.code in moves) {
      event.preventDefault();
      console.log(Boolean(move(moves[event.code])));
      renderBoard();
      console.log(boardToStr(), levelNumber());
    }
  });
};

const boardEl = document.getElementById("board");

var Module = {
  preRun: [],
  postRun: [initializeGame],
  print: text => console.log(text),
  printErr: text => console.error(text),
};

