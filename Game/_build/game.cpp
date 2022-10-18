#include "raylib.h"
#include "game.h"

void startGame()
{	
	int width = 1920;
	int height = 1080;

	InitWindow(width, height, "Game");

	while(!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(BLUE);

		EndDrawing();
	}
}