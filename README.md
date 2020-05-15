# PONG game SFML 2.5 C++

Classic retro game revisited using SFML 2.5 and C++


## Installation

Follow the tutorial at [SFML](https://www.sfml-dev.org/tutorials/2.5/start-vc.php) to install SFML.

## Usage

```c++

//At GameState.h
//Change this bool to enable pong as a CLOCK
bool clockBool = false;


//At GameState.cpp
//Changing CPU to 1 enables CPU play
this->player1 = new Player(mWindow, 1, /*bool CPU*/);
this->player2 = new Player(mWindow, 0, /*bool CPU*/);

```

## How to play

Player 1 - use the W|S keys
Player 2 - use the Arrow keys

## License
[MIT](https://choosealicense.com/licenses/mit/)