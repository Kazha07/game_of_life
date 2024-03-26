# Conway's Game of Life Simulation

This repository contains a C program that simulates Conway's Game of Life, a popular cellular automaton that models the life cycle of cells on a grid based on a set of rules. The simulation reads initial configurations from a BMP file and iterates through generations, displaying the state of the grid in the console.

## Features

- Reads initial grid state from a BMP file.
- Simulates the Game of Life rules.
- Displays each generation of cells in the console.
- Supports customizable grid sizes through a configuration file.

## Installation

Clone the repository to your local machine:

```bash
git clone https://github.com/Kazha07/game_of_life.git
cd game_of_life
```

## Configuration

Configuration File (*.txt):
- The file name must be `config.txt`.
- Parameters should be specified in the format `x=num`, not `x = num`.
- Both coordinates, `x` and `y`, need to be indicated.

Image (*.bmp file):
- The size of the image in pixels (px) must match the size specified in the configuration file.
- The image must be saved as a 24-bit BMP file format.
- The image should be named `game_grid.bmp`.
- The background color must be black.
- You may use any color except black.

File Location:
- All files, including the configuration file and the image, must be located in the same folder as the game.

After meeting these requirements, the game can be safely launched.

## Compilation

Compile the source code using the following command:

```bash
gcc -o GameOfLife game.c
```

## Running the Simulation

Execute the compiled program:

```bash
./GameOfLife
```

The program will display each generation of the cell grid in the console. The simulation runs until the cell configurations repeat or remain unchanged for two consecutive generations.

## Contributors

[Vipaloo](https://github.com/Vipaloo), [Kazha07](https://github.com/Kazha07)