# Project Proposal

## What's the proposal?

Our proposal is to create an implementation of the classic warehouse organization puzzle game Sokoban.

## How will it be helpful or enjoyable?

Our web-based Sokoban game will have greater user reachability compared to a more esoteric interface like the consoles or SDL2. The game will have both entertainment and educational value for developing logical reasoning and problem solving skills to a wide-range of audience who basically has a browser and an Internet.

## What technology will we use?

The game engine will be written in C++ and will be compiled to [WASM](https://en.wikipedia.org/wiki/WebAssembly) with [Emscripten](https://en.wikipedia.org/wiki/Emscripten) to power a HTML5/JS/CSS user interface. Unit testing will be done with [`doctest.h`](https://github.com/sheredom/utest.h) and end-to-end/integration testing will be done with [Puppeteer](https://github.com/puppeteer/puppeteer). We may use a front-end build or framework such as [React](https://reactjs.org/).

