# Project Proposal

## What's the proposal?

Our proposal is to create an implementation of the classic warehouse organization puzzle game [Sokoban](https://en.wikipedia.org/wiki/Sokoban).

## How will it be helpful or enjoyable?

Our web-based Sokoban game will have greater user reachability compared to a more esoteric interface like the console or SDL2. The game will have both entertainment and educational value for developing logical reasoning and problem-solving skills. It should appeal to a wide audience who might only have a browser and Internet access.


## What technology will we use?

The game engine will be written in C++ and will be compiled to [WASM](https://en.wikipedia.org/wiki/WebAssembly) with [Emscripten](https://en.wikipedia.org/wiki/Emscripten) to power a HTML5/JS/CSS user interface. Unit testing will be done with [`doctest.h`](https://github.com/doctest/doctest) and end-to-end/integration testing will be done with [Puppeteer](https://github.com/puppeteer/puppeteer). We may use a front-end build or framework such as [React](https://reactjs.org/).

