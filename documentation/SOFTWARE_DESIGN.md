# Software Design

## Project title and authors

Sokoban by Greg Gorlen

## Overview

Our proposal is to create an implementation of the puzzle game [Sokoban](https://en.wikipedia.org/wiki/Sokoban) in C++ that will be compiled to [WASM](https://en.wikipedia.org/wiki/WebAssembly) with [Emscripten](https://en.wikipedia.org/wiki/Emscripten) to power a HTML5/JS/CSS user interface (UI).

## Technical Architecture

The game engine back-end will be written in C++ and the UI front-end will be written in browser languages, HTML5/JavaScript/CSS. Optionally, we could use a component framework such as React or a typing system like TypeScript for the front-end, but since the application will be small, plain HTML/CSS/JS without a build stage may be simplest for starters.

Unit testing will be performed on the C++ game engine code using [`doctest.h`](https://github.com/doctest/doctest).

The browser user interface will be tested with [Jest](https://github.com/facebook/jest) and [Puppeteer](https://github.com/puppeteer/puppeteer/).

The turn-based nature of puzzle games and the HTML user interface makes it very easy to test our code, as opposed to a live action game on a screen where it'd be very difficult to programmatically provide input and assert on game state. Real-time graphics-based games can be math-heavy and asset-heavy.

There is a very clear separation between front- and back-ends, so we can delegate disjoint tasks and responsibilities. The back-end game logic can be written in C++ without any knowledge of JS (and could ideally be modular enough to couple with a command-line front-end that might be useful for development). Greg will mostly be responsible for linking the JS and C++ components together.

```
           BACKEND (game engine)

       .-------.
       | docTest |
       `-------`
           |
           v        [emscripten compilation]
.-----------------.          |
| C++ game engine |----------+--+
`-----------------`             |
                                |
................................|.............
                                |
.------.   FRONTEND (browser)   |
| User |                        |
`------`                        |
   |                            |
[click events]    [API calls]   |
   |                   |        v
   |   .----------.~~~~+~~~>.------.
   +-->| HTML5 UI |         | WASM |<--compiled backend engine
       `----------`<~~~+~~~~`------`
            ^          |
            |     [game state]
            |
            |
.----------------------.
| Jest/Puppeteer tests |
`----------------------`
```

Greg has built a simple proof-of-concept that illustrates the concept/workflow and relevant technologies interoperating: <https://github.com/ggorlen/wasm-click-counter>.

### Game engine back-end

The Sokoban game engine will consist of a top-level C++ class, `Sokoban`, which will expose the following interface:

```
// class constructor
Sokoban constructor(const vec<vec<string>> levels)

// class properties
const vec<vec<string>> levels, read-only
uint current_level // index into levels
uint moves
vec<string> board // the current board state which is mutated on move/undo/reset

// one of the possible states a cell can be in (could be char or enum)
char (or enum?) {
   ' ': empty space
   '#': impassable wall
   '.': goal cell
   '$': box
   '*': box on top of goal cell
   '@': player
   '+': player on top of goal cell
}

// one of the possible movement directions for the player
enum Direction {U, D, L, R}

// attempt a player move in direction (up/down/left/right) and return true/false to indicate if it was successful. internally, append to the history of moves made.
bool move(Direction direction)

// switch to level level_number if possible, throw otherwise
void change_level(uint level_number)

// reset the current level to its original state (could be replaced by change_level by passing in the current level number)
void reset()

// undo the last move
void undo()

// return the current board position as a 2d vector of characters or a vector of strings representing each row
vector<string> board()

// return the number of moves made on the current board
uint moves()

// return the current level number
uint level()

// return whether the current board is solved
bool solved()
```

Internally, levels will be a `vector<vector<vector<Cell>>>`, that is, a vector of sequential levels, each of which is a 2d vector representing the game board, with each cell being a character.

### User interface front-end

The user JS code will be responsible for handling user actions, calling the compiled C++ game engine functions, and rerendering the game board as needed.

- Upon load, JS will start at level 0 and call `board()` to get the starting board state. It will then render it to the DOM using HTML elements.
- JS will also provide buttons or keypresses to call corresponding reset/undo/change level functions.
- During level play, arrow keys move the player up/down/left/right. JS will set event listeners on these keys and call the relevant C++ function `move(direction)` Upon a successful move, JS will call `board()` to get the current board state and re-render the UI. It will also call `solved()` to determine if the last move solved the puzzle. If it did, `change_level()` will be called to move the game to the next level.

### API layer ("glue" between the front and back ends)

We'll use a wrapper on the game engine to instantate a Sokoban game at runtime and expose WASM-friendly functions for JS to call. This avoids putting burden on the game class to closely match the possibly strangely-defined WASM interface.

## Rough timeline

- Sprint 1: select the project and tech stack, and set up environment
- Sprint 2: complete design documents
- Sprint 3: set up classes, add level/board/cell data structure and movement controls and connect to UI
- Sprint 4: implement game logic for block pushing, prohibit illegal moves like walls
- Sprint 5: determine when the level is complete, add reset and undo functionality
- Sprint 6: assets, stretch goals and features, custom level design
- Sprint 7: stretch goals and polish

