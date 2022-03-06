# Testing Plan

## Testing Tools

We'll be unit testing the back-end (the Sokoban game engine written in C++) using [doctest](https://github.com/doctest/doctest) and integration/end-to-end testing the full stack of the application from the UI to the game engine with [Jest](https://jestjs.io/) and [Puppeteer](https://github.com/puppeteer/puppeteer).

## Testing Strategy

The back-end tests will include and call small parts of the game, ranging from single functions to small collections of functions. Since our game uses player movement input, the general approach will be calling a `move` function to take an action on the game board, then asserting that the resulting game board output (a 2d grid of characters) matches an expected grid. This ensures the game engine to be working as expected.

For the front-end tests, the same methodology will be applied, but it'll be acting upon the HTML5 UI calling WASM functions. This will validate that the full stack works, from the UI to the game engine by way of the API "glue code" exposing the game engine to the UI client. This will be a bit trickier than unit testing, since Puppeteer will be providing dynamic user input and selecting the grid squares via CSS selectors, depending on how we choose to represent the grid. But ultimately, it'll be the same idea: give input, check that the game board matches an expected game board after a series of actions.

In general, we're approaching testing bottom-up, with each unit function tested for its specific behavior, then integrating the game-engine and HTML5 UI and ensuring each behavior has the intended impact on the game state. We probably won't use much in the way of mocks.

## Test Cases

### Unit-level tests

- Should reset the current level to its original state.
- Should undo a move.
- Should allow the player to move up.
- Should allow the player to move down.
- Should allow the player to move left.
- Should allow the player to move right.
- Should not allow moving into a wall from the top.
- Should not allow moving into a wall from the bottom.
- Should not allow moving into a wall from the left.
- Should not allow moving into a wall from the right.
- Should allow the player to push a box up onto an empty space.
- Should allow the player to push a box down onto an empty space.
- Should allow the player to push a box left onto an empty space.
- Should allow the player to push a box right onto an empty space.
- Should not allow the player to push a box onto an impassable wall.
- Should allow the player to push a box right onto an empty goal cell.
- Should detect a solved board.
- Should detect an unsolved board.
- Should allow the user to switch levels.
- Should return the number of moves made on the current board.

### Integration/E2E-level tests

- Should show congratulatory message when a level is solved.
- Should allow the player to click on the desired level to play.
- Should display next level after clicking congratulatory message or change to a different level.
- Should reset the board by pressing the reset button.
- Should undo previous game state when pressing the undo button.
- Should initiate the default game when pressing the start button.
- When the directional key up is pressed, the player should move up one cell.
- Should move the player left when the left arrow is pressed and the destination square is empty.
- Should move the player right when the right arrow is pressed and the destination square is empty.
- Should move the player up when the up arrow is pressed and the destination square is empty.
- Should move the player down when the down arrow is pressed and the destination square is empty.
