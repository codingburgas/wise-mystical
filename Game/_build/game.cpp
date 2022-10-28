#include "raylib.h"
#include "game.h"
#include "activeCityAnimation.h"
#include "City.h"
#include <iostream>

void startGame()
{
	int width = 1920;
	int height = 1080;

	InitWindow(width, height, "Game");

	// Load map texture from the file structure
	Texture2D map = LoadTexture("../resources/map.png");
	Font comfortaaLight = LoadFontEx("../resources/Comfortaa-Light.ttf", 25, 0, 250);

	Vector2 mousePoint = { 0.0f, 0.0f };

	float cameraPosX = float(GetScreenWidth()) / 2;
	float cameraPosY = float(GetScreenHeight()) / 2;

	Camera2D camera = {};
	camera.offset = { float(width) / 2, float(height) / 2 };
	camera.target = { cameraPosX, cameraPosY };
	camera.zoom = 1;
	camera.rotation = 0;

	// Define city dynamic arra
	int citiesCounter = 2;

	Vector2 conCity1;
	Vector2 conCity2;
		
	// Define variables for active city animation
	animationFrame activeCityAnimationParts[3] = {
		{5, '+', frame1},
		{10, '+', frame6},
		{15, '+', frame10},
	};
	animationFrame* ptr = activeCityAnimationParts;

	while (!WindowShouldClose())
	{
		// Update camera position
		mousePoint = GetScreenToWorld2D(GetMousePosition(), camera);
		camera.target.x = cameraPosX;
		camera.target.y = cameraPosY;

		// Uptade camera position, based on W, A, S, D keys
		if (IsKeyDown(KEY_A))
		{
			// Check left camera boundary 
			if (cameraPosX > 910)
			{
				cameraPosX -= 3.0f;
			}
			else
			{
				cameraPosX += 3.0f;
			}

			// Check top or bottom key down
			if (IsKeyDown(KEY_W))
			{
				// Check top boundary
				if (cameraPosY > 550)
				{
					cameraPosY -= 3.0f;
				}
				else
				{
					cameraPosY += 3.0f;
				}
			}
			else if (IsKeyDown(KEY_S))
			{
				// Check bottom boundary
				if (cameraPosY < 2250)
				{
					cameraPosY += 3.0f;
				}
				else
				{
					cameraPosY -= 3.0f;
				}
			}
		}
		else if (IsKeyDown(KEY_D))
		{
			// Check right camera boundary 
			if (cameraPosX < 1815)
			{
				cameraPosX += 3.0f;
			}
			else
			{
				cameraPosX -= 3.0f;
			}

			// Check top or bottom key down
			if (IsKeyDown(KEY_W))
			{
				// Check top boundary
				if (cameraPosY > 550)
				{
					cameraPosY -= 3.0f;
				}
				else
				{
					cameraPosY += 3.0f;
				}
			}
			else if (IsKeyDown(KEY_S))
			{
				// Check bottom boundary
				if (cameraPosY < 2250)
				{
					cameraPosY += 3.0f;
				}
				else
				{
					cameraPosY -= 3.0f;
				}
			}
		}

		// Update camera, based on seperate key input - W, A, S, D 
		if (IsKeyDown(KEY_W))
		{
			if (cameraPosY > 550)
			{
				cameraPosY -= 3.0f;
			}
			else
			{
				cameraPosY += 3.0f;
			}
		}
		else if (IsKeyDown(KEY_S))
		{
			if (cameraPosY < 2250)
			{
				cameraPosY += 3.0f;
			}
			else
			{
				cameraPosY -= 3.0f;
			}
		}
		else if (IsKeyDown(KEY_A))
		{
			if (cameraPosX > 910)
			{
				cameraPosX -= 3.0f;
			}
			else
			{
				cameraPosX += 3.0f;
			}
		}
		else if (IsKeyDown(KEY_D))
		{
			if (cameraPosX < 1815)
			{
				cameraPosX += 3.0f;
			}
			else
			{
				cameraPosX -= 3.0f;
			}
		}

		BeginDrawing();
		
		// Set background color for the framebuffer 
		ClearBackground(mapBackgroundColor);

		// Begin 2D mode
		BeginMode2D(camera);

		// Draw the map on the screen
		DrawTextureEx(map, Vector2{ 0,0 }, 0, 1, mapColor);

		DrawTextEx(comfortaaLight, "Test", { float(GetScreenWidth() / 2) , float(GetScreenHeight() / 2) }, (float)comfortaaLight.baseSize, 2, BLACK);

		// Sample usage of drawActiveCityAnimation
		drawActiveCityAnimation(ptr, Vector2{ 570,810 });

		// End 2D mode
		EndMode2D();

		EndDrawing();
	}
}