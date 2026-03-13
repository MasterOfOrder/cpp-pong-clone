# C++ Pong

A two-player Pong clone built in C++ using SFML. First to 5 points wins.

## Controls

| Player 1 | Player 2 |
|----------|----------|
| W — Move Up | ↑ — Move Up |
| S — Move Down | ↓ — Move Down |

## Features

- Two player local multiplayer
- Smooth movement using delta time
- Pause between points with automatic ball and paddle reset
- Score tracking with win screen at 5 points
- Game state system (Playing, Paused, WinScreen)

## How To Compile & Run

Make sure you have SFML installed and a C++ compiler (g++ recommended).

```bash
g++ -o pong main.cpp -lsfml-graphics -lsfml-window -lsfml-system
./pong
```

On Windows:
```bash
g++ -o pong main.cpp -lsfml-graphics -lsfml-window -lsfml-system
pong.exe
```

> The font file `ARIAL.TTF` must be in the same directory as the executable.
> Make sure the SFML .dll files are in the same directory as the executable. These come with your SFML installation.

## Built With

- C++
- SFML

## Author

**masteroforder** — [github.com/masteroforder](https://github.com/masteroforder)
