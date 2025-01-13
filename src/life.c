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

void spawnTestGlider(int grid[AMOUNT_OF_CELLS][AMOUNT_OF_CELLS], int posX, int posY)
{
	grid[posX+1][posY] = ALIVE_CELL;
    grid[posX+2][posY+1] = ALIVE_CELL;
    grid[posX][posY+2] = ALIVE_CELL;
    grid[posX+1][posY+2] = ALIVE_CELL;
    grid[posX+2][posY+2] = ALIVE_CELL;
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