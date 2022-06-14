# Modified Sokoban project
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
I'm using the `gh-pages` branch and the `docs` folder to deploy to <https://ggorlen.github.io/cs195-project>. Here's the deployent workflow:

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
