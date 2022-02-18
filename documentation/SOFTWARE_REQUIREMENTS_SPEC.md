# Sokoban 

#### by Greg Gorlen, Severin Light, Juan Rangel Espinoza, and Irvin Tancioco

## Overview

Our proposal is to create an implementation of the puzzle game [Sokoban](https://en.wikipedia.org/wiki/Sokoban) in C++ that will be compiled to [WASM](https://en.wikipedia.org/wiki/WebAssembly) with [Emscripten](https://en.wikipedia.org/wiki/Emscripten) to power a HTML5/JS/CSS user interface (UI).

## Goals and Purpose

Our web-based Sokoban game will have greater user reachability compared to a more esoteric interface like the console or SDL2. The game will have both entertainment and educational value for developing logical reasoning and problem-solving skills. It should appeal to a wide audience who might only have a browser and Internet access.

## Requirements

### Phase 1: Basic Gameplay Requirements

#### World

* The world shall be approximately 500 pixels tall by 600 pixels wide.
* The world shall have top view perspective (viewed from above). 
* Every element in the world shall have a graphical dimensions of 20 pixels by 20 pixels.
* The world shall contain the following:
    - main character
    - impassable walls
    - floors
    - boxes
    - goal cells

#### Main Character

* The main character shall have four main movements: Upward(U), Downward (D), Left (L) and Right (R).
* These movements shall be controlled by key presses. For example: if the user presses the UP button, the character will move one cell to the north, or if the user presses the DOWN button, the character will move one cell to the south. 
* The character shall be allowed to move one tile at a time if its path is unobstructed. A path is unobstructed if the cell adjacent to the character or the box being pushed is an empty cell.
* The character shall be able to push on an existing box if its path is unobstructed.
* The charater shall be able to only occupy an empty cell.
* The character shall be only allowed to move within the constraints of the world.

## Functional Requirements

#### Win / Loss / Score

* In order for the user to clear a level, the user has to move all the boxes in the goal cells.
* The score shall be tracked by counting the total number of moves the user takes to place all boxes in all of the existing goal cells.
* The user shall be allowed to undo their previous moves.

## Use Cases

### Phase 2: New Game Features (Optional)
* The game should have multi-player option.
* Each level should have additional element added to the world. For example, converyor belts, teleporters, boxes that decay when pushed, ice floors that boxes slide on, multiple players that move in tandem, etc.
* AI generated optimized solution. With the given world, the game should have a hint feature showing the optimal moves to solve the world.

### System Requirements
The game shall be run on any browser that supports WASM (Safari, Chrome, Firefox, Edge, Opera, IOS Safari, Firefox for Android)

### Use Cases
* The user presses the start button to initiate the game. A prompt will display asking for the user to enter level. A static world elements will be displayed on the screen.
* The user can press any directional keys to move around the world.
* When all of the boxes are placed on the goal cells, a congratulatory message and stats will be displayed. The user will be asked to play again.
