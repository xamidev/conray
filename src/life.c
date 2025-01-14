/**
* @file src/life.c
* @brief Cellular automaton implementation
* 
* @copyright
* Anyone is free to copy, modify, publish, use, compile, sell, or
* distribute this software, either in source code form or as a compiled
* binary, for any purpose, commercial or non-commercial, and by any
* means.
* 
* In jurisdictions that recognize copyright laws, the author or authors
* of this software dedicate any and all copyright interest in the
* software to the public domain. We make this dedication for the benefit
* of the public at large and to the detriment of our heirs and
* successors. We intend this dedication to be an overt act of
* relinquishment in perpetuity of all present and future rights to this
* software under copyright law.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
* OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
* 
* For more information, please refer to <https://unlicense.org/>
*/

#include <stddef.h>
#include "life.h"
#include "raylib.h"
#include <stdlib.h>

void spawnTestGlider(int grid[AMOUNT_OF_CELLS][AMOUNT_OF_CELLS], int posX, int posY)
{
	grid[posX+1][posY] = ALIVE_CELL;
    grid[posX+2][posY+1] = ALIVE_CELL;
    grid[posX][posY+2] = ALIVE_CELL;
    grid[posX+1][posY+2] = ALIVE_CELL;
    grid[posX+2][posY+2] = ALIVE_CELL;
}

int countCellNeighbors(int grid[AMOUNT_OF_CELLS][AMOUNT_OF_CELLS], int posX, int posY)
{
    int neighbors = 0;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0) continue;
            int newX = posX + i;
            int newY = posY + j;
            if (newX >= 0 && newX < AMOUNT_OF_CELLS && newY >= 0 && newY < AMOUNT_OF_CELLS) {
                neighbors += grid[newX][newY]; // because ALIVE is 1
            }
        }
    }

    return neighbors;
}

void drawGrid(int grid[AMOUNT_OF_CELLS][AMOUNT_OF_CELLS])
{
    for (size_t i=0; i<AMOUNT_OF_CELLS; i++)
    {
        for (size_t j=0; j<AMOUNT_OF_CELLS; j++)
        {
            if (grid[i][j] == ALIVE_CELL) {
                DrawRectangle(CELL_SIZE_PIXELS*i, CELL_SIZE_PIXELS*j, CELL_SIZE_PIXELS, CELL_SIZE_PIXELS, BLACK);
            } else {
                DrawRectangle(CELL_SIZE_PIXELS*i, CELL_SIZE_PIXELS*j, CELL_SIZE_PIXELS, CELL_SIZE_PIXELS, WHITE);
            }
        }
    }
}

void copyGrid(int src[AMOUNT_OF_CELLS][AMOUNT_OF_CELLS], int dest[AMOUNT_OF_CELLS][AMOUNT_OF_CELLS])
{
    for (size_t i=0; i<AMOUNT_OF_CELLS; i++)
    {
        for (size_t j=0; j<AMOUNT_OF_CELLS; j++)
        {
            dest[i][j] = src[i][j];
        }
    }
}

void updateGrid(int grid[AMOUNT_OF_CELLS][AMOUNT_OF_CELLS]) {
    int temp[AMOUNT_OF_CELLS][AMOUNT_OF_CELLS] = {0};

    for (int i = 0; i < AMOUNT_OF_CELLS; i++) {
        for (int j = 0; j < AMOUNT_OF_CELLS; j++) {
            int neighbors = countCellNeighbors(grid, i, j);

            if (grid[i][j] == ALIVE_CELL) {
                if (neighbors < 2 || neighbors > 3) {
                    temp[i][j] = DEAD_CELL;
                } else {
                    temp[i][j] = ALIVE_CELL;
                }
            } else if (grid[i][j] == DEAD_CELL) {
                if (neighbors == 3) {
                    temp[i][j] = ALIVE_CELL;
                } else {
                    temp[i][j] = DEAD_CELL;
                }
            }
        }
    }

    copyGrid(temp, grid);
}

void clearGrid(int grid[AMOUNT_OF_CELLS][AMOUNT_OF_CELLS])
{
    for (size_t i=0; i<AMOUNT_OF_CELLS; i++)
    {
        for (size_t j=0; j<AMOUNT_OF_CELLS; j++)
        {
            grid[i][j] = DEAD_CELL;
        }
    }
}

void initSoup(int grid[AMOUNT_OF_CELLS][AMOUNT_OF_CELLS])
{
    for (size_t i=0; i<AMOUNT_OF_CELLS; i++)
    {
        for (size_t j=0; j<AMOUNT_OF_CELLS; j++)
        {
            grid[i][j] = rand() % 101 > 70 ? ALIVE_CELL : DEAD_CELL;
        }
    }
}

void toggleCell(int grid[AMOUNT_OF_CELLS][AMOUNT_OF_CELLS], int posX, int posY)
{
    switch(grid[posX][posY])
    {
        case ALIVE_CELL:
            grid[posX][posY] = DEAD_CELL;
            break;
        case DEAD_CELL:
            grid[posX][posY] = ALIVE_CELL;
            break;
        default:
            break;
    }
}