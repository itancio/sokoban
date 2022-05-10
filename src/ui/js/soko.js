/**
 * This module provides an interface into the game engine.
 * No methods are available until Emscripten has completed loading.
*/
const soko = {};

moduleReady.then(() => {
  Module.ccall("sokoban_initialize");
  const methods = {
    move: Module.cwrap(
      "sokoban_move", // name of C function
      "bool",         // return type
      ["string"],     // argument types
    ),
    boardToStr: Module.cwrap(
      "sokoban_board_to_string",
      "string", // return type
    ),
    changeLevel: Module.cwrap(
      "sokoban_change_level",
      "bool",
      ["number"]
    ),
    goto: Module.cwrap(
      "sokoban_goto",
      "bool",
      ["number", "number"]
    ),
    levelNumber: Module.cwrap("sokoban_level"),
    levelsSize: Module.cwrap("sokoban_levels_size"),
    reset: Module.cwrap("sokoban_reset"),
    sequence: Module.cwrap("sokoban_sequence", "string"),
    solved: Module.cwrap("sokoban_solved", "bool"),
    undo: Module.cwrap("sokoban_undo", "bool"),
  };
  Object.assign(soko, methods);
});

export default soko;
