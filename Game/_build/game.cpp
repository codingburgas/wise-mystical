#include "raylib.h"
#include "game.h"

void startGame()
{	
	int width = 1920;
	int height = 1080;

	InitWindow(width, height, "Game");

	// Load map texture from the file structure
	Texture2D map = LoadTexture("../resources/map.png");

	while(!WindowShouldClose())
	{
		BeginDrawing();

		// Set background color for the framebuffer
		ClearBackground(mapBackgroundColor);

		// Draw the map on the screen
		DrawTextureEx(map, Vector2{ 0,0 }, 0, 1, RAYWHITE);

		EndDrawing();
	}
}