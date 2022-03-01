# Testing Plan

## Testing Tools

We'll be unit testing the back-end (the Sokoban game engine written in C++) using [doctest](https://github.com/doctest/doctest) and integration/end-to-end testing the full stack of the application from the UI to the game engine with [Jest](https://jestjs.io/) and [Puppeteer](https://github.com/puppeteer/puppeteer).

## Testing Strategy

The back-end tests will include and call small parts of the game, ranging from single functions to small collections of functions. Since our game uses player movement input, the general approach will be calling a `move` function to take an action on the game board, then asserting that the resulting game board output (a 2d grid of characters) matches an expected grid. This ensures the game engine to be working as expected.

For the front-end tests, the same methodology will be applied, but it'll be acting upon the HTML5 UI calling WASM functions. This will validate that the full stack works, from the UI to the game engine by way of the API "glue code" exposing the game engine to the UI client. This will be a bit trickier than unit testing, since Puppeteer will be providing dynamic user input and selecting the grid squares via CSS selectors, depending on how we choose to represent the grid. But ultimately, it'll be the same idea: give input, check that the game board matches an expected game board after a series of actions.

In general, we're approaching testing bottom-up, with each unit function tested for its specific behavior, then integrating the game-engine and HTML5 UI and ensuring each behavior has the intended impact on the game state. We probably won't use much in the way of mocks.

## Test Cases

### Unit-level tests

- Test that impassible walls are impassible by the player.
- Test that the level is complete/congratulatory message when and only when all boxes are moved to designated goal cells.
- Test when a level is complete, the user is prompted to move to the next level or jump to a different level.
- Test that all boxes are pushable by the player.
- Test the score is tracking player movement.
- Test that the undo button undoes moves.
- Test the reset button reset’s the board properly.
- Test that the 'Sart' button initiates the default game by dropping the player into level 1.
- Test that the drop-down menu is clickable by the player and allows them to jump to different levels.
- Test that the directional keys move the character in the proper direction up, down, left, and right.

### Integration/E2E-level tests

- TBD 10
