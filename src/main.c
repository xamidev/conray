/**
* @file src/main.c
* @brief Conway's game of Life in C with Raylib
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

#include "raylib.h"
#include "resource_dir.h"
#include "life.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/*
	- see last fresh dead cells as decaying colors
	- have a geneartion counter
*/

typedef enum GameScreen
{
	TITLE = 0,
	GAME
} GameScreen;

int main(void)
{
	static bool paused = false;
	srand(time(NULL));
	int grid[AMOUNT_OF_CELLS][AMOUNT_OF_CELLS] = {DEAD_CELL};

	GameScreen currentScreen = TITLE;
	
	spawnTestGlider(grid, 5, 5);
	static int screenSize = AMOUNT_OF_CELLS*CELL_SIZE_PIXELS;	

	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	// Create the window and OpenGL context
	InitWindow(screenSize, screenSize, "Conway's Game of Life");

	SetTargetFPS(TARGET_FPS);
	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		/* Updates */
		switch (currentScreen)
		{
			case TITLE:
				if (IsKeyPressed(KEY_SPACE)) {
					currentScreen = GAME;
				}
				break;
			case GAME:
				if (IsKeyPressed(KEY_N)) {
					// New Soup
					clearGrid(grid);
					initSoup(grid);
					ClearBackground(WHITE);
					drawGrid(grid);
				}
				if (IsKeyPressed(KEY_C)) {
					clearGrid(grid);
					ClearBackground(WHITE);
				}
				if (IsKeyPressed(KEY_P)) {
					if (paused) {
						paused = false;
					} else {
						paused = true;
					}
					updateGrid(grid);
					drawGrid(grid);
				}
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					Vector2 cellPosition = {0.0f, 0.0f};
					cellPosition = GetMousePosition();
					printf("Mouse clicked @ x=%.2f y=%.2f\n", cellPosition.x, cellPosition.y);
					int i = cellPosition.x/CELL_SIZE_PIXELS;
					int j = cellPosition.y/CELL_SIZE_PIXELS;
					toggleCell(grid, i, j);
					drawGrid(grid);
				}
				break;
			default:
				break;
		}

		/* Drawing */
		BeginDrawing();
		switch (currentScreen)
		{
			case TITLE:
				int titleWidth = MeasureText("Conway's game of Life", 40);
				DrawRectangle(0, 0, screenSize, screenSize, DARKBLUE);
				DrawText("Conway's game of Life", (screenSize-titleWidth)/2, 20, 40, WHITE);
				int controlsWidth = MeasureText("Controls", 30);
				DrawText("Controls", (screenSize-controlsWidth)/2, 100, 30, WHITE);
				DrawText("N to spawn soup", 25, 150, 30, WHITE);
				DrawText("C to clear grid", 25, 200, 30, WHITE);
				DrawText("P to pause simulation", 25, 250, 30, WHITE);
				DrawText("Left click to toggle cell", 25, 300, 30, WHITE);
				int startGameWidth = MeasureText("Press Space to start!", 30);
				DrawText("Press Space to start!", (screenSize-startGameWidth)/2, 400, 30, WHITE);
				break;
			case GAME:
				if (!paused)
				{
					ClearBackground(WHITE);
					drawGrid(grid);
					updateGrid(grid);
				}
				break;
			default:
				break;
		}
		EndDrawing();
		
	}

	CloseWindow();
	return 0;
}
