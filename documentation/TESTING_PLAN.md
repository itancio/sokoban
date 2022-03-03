# Testing Plan

## Testing Tools

We'll be unit testing the back-end (the Sokoban game engine written in C++) using [doctest](https://github.com/doctest/doctest) and integration/end-to-end testing the full stack of the application from the UI to the game engine with [Jest](https://jestjs.io/) and [Puppeteer](https://github.com/puppeteer/puppeteer).

## Testing Strategy

The back-end tests will include and call small parts of the game, ranging from single functions to small collections of functions. Since our game uses player movement input, the general approach will be calling a `move` function to take an action on the game board, then asserting that the resulting game board output (a 2d grid of characters) matches an expected grid. This ensures the game engine to be working as expected.

For the front-end tests, the same methodology will be applied, but it'll be acting upon the HTML5 UI calling WASM functions. This will validate that the full stack works, from the UI to the game engine by way of the API "glue code" exposing the game engine to the UI client. This will be a bit trickier than unit testing, since Puppeteer will be providing dynamic user input and selecting the grid squares via CSS selectors, depending on how we choose to represent the grid. But ultimately, it'll be the same idea: give input, check that the game board matches an expected game board after a series of actions.

In general, we're approaching testing bottom-up, with each unit function tested for its specific behavior, then integrating the game-engine and HTML5 UI and ensuring each behavior has the intended impact on the game state. We probably won't use much in the way of mocks.

## Test Cases

### Unit-level tests

- undo() should load the previous game state.
- reset() should the current level to its original state.
- move(U) should allow player to move up.
- move(D) should allow player to move down.
- move(L) should allow player to move left.
- move(R) should allow player to move right.
- player should not be able to pass through impassable walls when move(U).
- player should not be able to pass through impassable walls when move(D).
- player should not be able to pass through impassable walls when move(L).
- player should not be able to pass through impassable walls when move(R).
- change_level(uint level_number) should allow user to switch levels.
- moves() should return the number of moves made on the current board.
- solved() should return true when all the boxes are on top of goal cells.

### Integration/E2E-level tests

- When level is solved() congratulatory message should appear.
- When level is solved() the user should be prompted to move to the next level or change to a different level.
- When pushed/clciked reset() should reset the board
- When pushed/clicked undo() should undo previous game state.
- When pushed/clicked Start button should initiatie the deafult game by returnting level().
- When directional key up is pressed player should move up one.
- When directional key down is pressed player should move down one.
- When directional key left is pressed player should move left one.
- When directional key right is pressed player should move right one. 
