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

int main(void)
{
	int grid[AMOUNT_OF_CELLS][AMOUNT_OF_CELLS] = {DEAD_CELL};
	
	spawnTestGlider(grid, 5, 5);		

	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	// Create the window and OpenGL context
	InitWindow(600, 600, "Conway's Game of Life");

	/*
	Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");
	*/
	
	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(RED);

		drawGrid(grid);

		// draw some text using the default font
		// DrawText("Game",0,0,20,RED);

		// draw our texture to the screen
		// DrawTexture(wabbit, 400, 200, WHITE);
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	/*
	cleanup
	unload our texture so it can be cleaned up
	UnloadTexture(wabbit);
	*/

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
