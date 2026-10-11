# Game of Life

A console implementation of Conway's Game of Life in C++, written in plain C style with linked lists and a Model/View/Controller structure.

You draw a starting pattern on a grid of up to 60x60 cells, then watch it evolve generation by generation, at a speed you choose or step by step.

## Features

- Grid size from 10x10 up to 60x60
- Add or remove live cells by coordinates
- Dead neighbors of live cells can be shown (`+`) or hidden
- Simulation with a chosen number of generations, step by step or at slow / medium / fast speed
- Save the current generation to a text file and load it back later

| Symbol | Meaning |
|:------:|---------|
| `O` | live cell |
| `.` | dead cell |
| `+` | dead cell next to a live one |

## How to run

**Windows (no compiler needed):** download `JogoDaVida.exe` from the [Releases](../../releases) page and run it.

**From source:** requires Windows and a C++ compiler such as MinGW g++. Only the main file needs to be compiled, because it includes the others:

```
g++ src/JV-IJR-Projeto.cpp -o JogoDaVida
```

Saved generations are written to `geracoes.txt` in the folder where the program is run.

## How it works

The game state is kept in three linked lists (live cells, dead neighbors, next generation) instead of scanning the whole grid on every step.

| File | Role |
|------|------|
| `JV-IJR-Model` | Lists, grid, game rules, save/load |
| `JV-IJR-View` | Screen output and input validation |
| `JV-IJR-Controller` | Menu loop and simulation control |
| `JV-IJR-Projeto.cpp` | Entry point (`main`) |

