# Project Proposals

## Greg's Proposal

#### What's the proposal?

My proposal is to create a C or C++ puzzle or board game backend that will be compiled to [WASM](https://en.wikipedia.org/wiki/WebAssembly) with [Emscripten](https://en.wikipedia.org/wiki/Emscripten) to power a HTML5/JS/CSS user interface.

#### How will it be tested?

Unit testing will be performed on the C/C++ code using a library like [Criterion](https://github.com/Snaipe/Criterion) (for C) or [Google Test](https://github.com/google/googletest) (for C++). The browser user interface will be tested with [Jest](https://github.com/facebook/jest) and [Puppeteer](https://github.com/puppeteer/puppeteer/).

#### Why is this a good idea?

The main selling point is that the turn-based nature of puzzle/strategy games and the HTML user interface makes it very easy to test our code (a key deliverable for the course), as opposed to a live action game on a screen where it'd be very difficult to programmatically provide input and assert on game state. Real-time graphics-based games can be math-heavy and asset-heavy.

Furthermore, the web-based UI makes the product much more accessible to the average user than more esoteric interfaces like the console, SDL2 or SFML which are hard to install. We get the best of JS/HTML, which I have a good amount of experience in, plus C/C++ for those who are more comfortable with it. If we have time and motivation to add multiplayer features, that's easy to do.

Puzzle/board games also generally don't require the investment in developing story, characters and assets which could be a major time sink if we pursued an interactive turn-based RPG (although that would be easy to test).

There is a very clear separation between front- and back-ends, so we can delegate disjoint tasks and responsibilities. The back-end game logic and AI can be written in C/C++ without any knowledge of JS (and could ideally be modular enough to couple with a command-line front-end that might be useful for development), and I (Greg) am comfortable handle linking the JS and C/C++ components together.

Finally, all of these technologies are popular and industry-relevant, and the scope of the project is flexible. It should be educational!

#### Do you have a proof of concept?

I've built a simple proof-of-concept that illustrates the concept/workflow and relevant technologies interoperating: <https://github.com/ggorlen/wasm-click-counter>.

#### Division of responsibilities

We can divide responsibilities up for the project roughly as follows (feel free to weigh in on your preferred role -- I'm just guessing for now):

- Greg will be responsible for project management, the HTML/JS user interface, Puppeteer integration testing, and any other JS needs. He'll be responsible for keeping the project glued together. He might also be involved in the C/C++ engine as needed.
- Someone to focus on C/C++ computer engine AI
- Someone to focus on C/C++ game engine mechanics
- Someone to work a bit on both AI, game mechanics and back-end unit tests, and to work with Greg to provide an API interface from the C/C++ code to the front-end

Optionally, if there's interest in HTML/JS from one of the team members I'm assuming prefers C/C++, Greg is happy to share those duties.

#### Further details

The game itself is flexible:
- If someone on the team is passionate about game design prefers to focus on that instead of coding (please volunteer!), then we can try designing our own game. This might be a lot of work and could slow down jumping into coding.
- Otherwise, we should pick an established game so we can focus on implementation.
  - One option is a turn-based, two-player abstract strategy game. We can dial up or down the coding difficulty by picking different games like Connect 4 (easy), Checkers (medium) or Chess (harder). We could pick a more obscure game from the hundreds avaiable in the [list of abstract strategy games](https://en.wikipedia.org/wiki/List_of_abstract_strategy_games).
  - Another option is a one-player [puzzle game](https://en.wikipedia.org/wiki/List_of_puzzle_video_games). AI and multiplayer would be less important here, but we could still integrate social aspects or potentially write a solver for it, depending on the difficulty.

As a potential stretch goal, I'd be interested in adding a socket.io-based multiplayer element and running a server on Heroku.

#### Architecture diagram

```
                   BACKEND

.-----------------------.
| Criterion/Google Test |
`-----------------------`
           |
           v          [emscripten compilation]
.-------------------.        |
| C/C++ game engine |--------+--+
`-------------------`           |
                                |
..............................................
                                |
                   FRONTEND     |
                                |
                [click events]  |
                       |        v
       .----------.~~~~+~~~>.------.
       | HTML5 UI |         | WASM |<--compiled backend engine
       `----------`<~~~+~~~~`------`
            ^          |
            |     [game state]
            |
            |
.----------------------.
| Jest/Puppeteer tests |
`----------------------`
```

If we decide to integrate a server and multiplayer, then WASM can run in NodeJS/Express and we can use Socket.io for client/server communication.

---

