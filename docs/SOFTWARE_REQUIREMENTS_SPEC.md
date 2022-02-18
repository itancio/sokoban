Our proposal is to create an implementation of the puzzle game [Sokoban](https://en.wikipedia.org/wiki/Sokoban) in C++ that will be compiled to [WASM](https://en.wikipedia.org/wiki/WebAssembly) with [Emscripten](https://en.wikipedia.org/wiki/Emscripten) to power a HTML5/JS/CSS user interface (UI).

## Goals and Purpose

Our web-based Sokoban game will have greater user reachability compared to a more esoteric interface like the console or SDL2. The game will have both entertainment and educational value for developing logical reasoning and problem-solving skills. It should appeal to a wide audience who might only have a browser and Internet access.

## Glossary
*Unobstructed path*
A path is unobstructed if the cell adjacent to the character or the box that the character is pushing is an empty cell.

## Requirements

### Gameplay Requirements

#### World

* The world shall be approximately 500 pixels tall by 600 pixels wide.

* The world shall have top view perspective (viewed from above). 

* The world elements shall be presented in a two dimensional configuration.

* Every element in the worlds shall have a graphical dimensions of 20 pixels by 20 pixels.

* The world shall contain the following:
    - main character
    - walls
    - floors
    - boxes
    - goal cells

#### Main Character
* The main character's appearance sh
* The main character shall have four main movements: Upward(U), Downward (D), Left (L) and Right (R).
* These movements shall be controlled by key presses. For example: if the user presses the UP button, the character will move one cell to the north, or if the user presses the DOWN button, the character will move one cell to the south. 
* The character shall be allowed to move one tile at a time if its path is [unobstructed](#glossary). 
* The character shall be able to push on an existing box if its path is [unobstructed](#glossary).
* The charater shall be able to only occupy an empty cell.
* The character shall be only allowed to move within the constraints of the world.


#### Win / Loss / Score
* In order for the user to clear a level, the user has to move all the boxes in the goal cells.
* The user will be allowed to undo his/her/their previous move/s.


### System Requirements
The 


## Use Cases


