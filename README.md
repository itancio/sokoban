# Sokoban

[game demo](https://itancio.github.io/sokoban/)

## Project Description
Sokoban app is a digital recreation of the traditional Sokoban game, where players must navigate a warehouse operative (the player) to push boxes to their designated storage locations. Designed with robustness in mind, the game is initialized with multiple levels and ensures that players can seamlessly switch between them.

<img src="assets/sokoban-title.png" width="80%"/>

The core of the game revolves around grid-based movements, where players can push boxes, move to an empty space, or navigate towards a goal. The app is has an undo and redo feature, ensuring mistakes can be corrected without starting over. Beyond simple movements, the game boasts an automatic pathfinding system, where given a set of coordinates, it calculates and moves the player along the optimal path.

<img src="assets/sokoban-game.png" width="80%" />

An essential tool for learning and strategizing, the game offers a 'rewind' feature, allowing players to revert multiple moves until a significant game event occurs. To assist with pattern recognition and strategy development, the simulator provides a move sequence tracker, presenting moves in a string format.

Under the hood, the game leverages data structures like queues, stacks, and unordered maps to efficiently handle game states, movements, and level histories. The Sokoban Simulator not only offers nostalgic gameplay but also stands as a testament to the seamless integration of classic games with modern-day programming techniques.

Potential Areas of Improvements
Level Design and Complexity: Introduce a diverse set of levels that vary in complexity, ensuring that both new players and Sokoban veterans are catered to.
Save and Load Feature: Allow players to save their current progress and load it at a later time, offering more flexibility in gameplay.
Custom Level Creation: Implement a level editor that lets users design and share their custom levels with the community.
Hint System: Incorporate a hint system for players who get stuck, providing clues or suggesting possible moves.
Leaderboards and Scoring: Introduce a scoring system based on the number of moves or time taken to complete a level. This could be coupled with leaderboards to encourage competitive gameplay.
Animations: Add smooth transitions and animations for movements, box pushes, and level completions to enhance the game's visual feedback.
Sound Effects and Music: Incorporate background music and sound effects for actions like box pushes, player moves, and level completions to enhance immersion.
Multiplayer Mode: Allow players to compete or collaborate in real-time, adding a new dimension to the gameplay.
Performance Optimization: Continually profile and optimize the code, especially the pathfinding algorithm, to ensure smooth gameplay even on large or complex levels.
Adaptive Difficulty: Implement a system that adjusts the game's difficulty based on a player's performance, offering a tailored challenge.
Mobile Integration: With the rising popularity of mobile games, developing a mobile-friendly version or app could reach a broader audience.



-----

# Instructions
This is a modified version of the original team-project for the Software Engineering course at CCSF, an implementation of [Sokoban](https://en.wikipedia.org/wiki/Sokoban) using Emscripten to generate [WASM](https://webassembly.org/) from C++ with a HTML5 front-end, [Puppeteer](https://github.com/puppeteer/puppeteer) for end-to-end testing and [doctest](https://github.com/doctest/doctest/) for unit testing.

Play the original game at <https://ggorlen.github.io/cs195-project/>.

## Windows installation
The main dependency is [Emscripten](https://emscripten.org/), which happens to depend on Node and Python which are also used in this project. On Windows, I used [Chocolatey](https://community.chocolatey.org/packages/emscripten) to install Emscripten with [this script](https://github.com/aminya/chocolatey-emscripten), running `choco install emscripten -y`. The script can also be used without Chocolatey. Once `emsdk` is available, I followed the setup shown [in the Emscripten docs](https://emscripten.org/docs/getting_started/downloads.html):

```powershell
./emsdk install latest
./emsdk activate latest

# export `emcc`, `npm`, `node`, `python`, etc to the path
C:\Users\<your user name>\AppData\Local\emsdk\emsdk_env.ps1
```

Once you have a prompt with the exported path using `emsdk_env.ps1`, clone or download this repo and run `cd ~/path/to/cs195-project`.

Download `doctest.h`, e.g. `wget https://raw.githubusercontent.com/doctest/doctest/master/doctest/doctest.h -O tests/engine/doctest.h`. You'll need `make` and `g++` (we had success with MinGW 8.1.0 and 8.3.0).

Finally, run `npm i` from the `cs195-project` directory to install Jest, Nodemon and Puppeteer to `node_modules`.

## Windows build/run/test

### Back-end game engine (C++)
Tests go in `tests/engine` along with [`doctest.h`](https://raw.githubusercontent.com/doctest/doctest/master/doctest/doctest.h). Run `make test` in that directory.

### Front-end UI (HTML/JS)
Make sure you've exported the path using `.\emsdk_env.ps1` described in the above section.

These are the build/run/test commands from `package.json`:
- `npm run build` compiles `sokoban.wasm` and `sokoban.js` from the `src/engine` files to the `dist` directory, builds a `sokoban.data` file from the levels in `src/engine/levels` and copies `ui` files to the `dist` directory (there's no bundling step for the front-end yet).
- `npm run start` starts the Python web server. Navigate to <http://localhost:8000/dist> to use the application.
- `npm run test` runs Jest/Puppeteer. This will fail if localhost from the above step isn't running.
- `npm run watch-backend` runs nodemon and `make test` for unit testing the C++ engine code.

The typical UI development workflow is to run `npm run start`, then run `nodemon` to automatically execute `npm run build && npm run test` whenever a source file changes.

## Deploying to GitHub pages
First, create a new branch named gh-pages. Then go to Settings > Pages. Set the `source` branch to `gh-pages` and `folder` to `/docs`.
This will deploy to <https://itancio.github.io/sokoban>. Here's the deployent workflow:

```
git checkout gh-pages
git merge main
npm run build
npm run deploy
git add docs*
git commit -m "Deploy something"
git pull
git push
```
