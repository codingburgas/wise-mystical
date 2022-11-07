#include <iostream>
#include "raylib.h"
#include "game.h"
#include "activeCityAnimation.h"
#include "cityOperations.h"
#include "travelLogic.h"

void startGame()
{
	int width = 1920;
	int height = 1080;

	InitWindow(width, height, "Game");

	// Load map texture from the file structure
	Texture2D map = LoadTexture("../resources/images/map.png");	

	// Load UI from the file structure
	Texture2D scoreBoard = LoadTexture("../resources/images/Score board.png");
	Texture2D popUp = LoadTexture("../resources/images/Travel pop-up.png");

	// Load font from the file structure
	Font comfortaaRegular = LoadFontEx("../resources/font/Comfortaa-Regular.ttf", 25, 0, 250);

	// Mouse position
	Vector2 mousePoint = { 0.0f, 0.0f };

	// Camera position
	float cameraPosX = float(GetScreenWidth()) / 2;
	float cameraPosY = float(GetScreenHeight()) / 2;
	
	// Position of testing button
	Vector2 button1Pos = { GetScreenWidth() - 30, GetScreenHeight() - 30 };

	// Declare game camera
	Camera2D camera = {};
	camera.offset = { float(width) / 2, float(height) / 2 };
	camera.target = { cameraPosX, cameraPosY };
	camera.zoom = 1;
	camera.rotation = 0;

	// Define city dynamic arra
	int citiesCounter = 40;

	// Vector for all cities
	City cities[40];
	City* ptr1 = intialiseCitiesArray(cities);
	ptr1 = cities;
	
	//
	int startCityNum = GetRandomValue(0, 39);
	Vector2 conCity1 = cities[startCityNum].coordinates;
	Vector2 conCity2 = {};

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
		mousePoint = GetScreenToWorld2D({ GetMousePosition().x, GetMousePosition().y + 40 }, camera);
		camera.target.x = cameraPosX;
		camera.target.y = cameraPosY;

		//
		button1Pos = GetScreenToWorld2D(Vector2{ float(GetScreenWidth()) - 450, float(GetScreenHeight()) - 120 }, camera);

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

		/*
			if (CheckCollisionPointRec(mousePoint, Rectangle{ button1Pos.x, button1Pos.y, 200, 90 }))
			{
				if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					conCity2 = goToNextCity(mousePoint, cities, citiesCounter);
				}
			}
		*/

		BeginDrawing();
		
		// Set background color for the framebuffer 
		ClearBackground(mapBackgroundColor);

		// Begin 2D mode
		BeginMode2D(camera);

		// Draw the map on the screen
		DrawTextureEx(map, Vector2{ 0,0 }, 0, 1, mapColor);

		// Draw city markers on the map
		drawCityPoints(ptr1, citiesCounter, comfortaaRegular);

		// Mark the current active city mark
		drawActiveCityAnimation(ptr, cities[1].coordinates);

		// Testing button
		// DrawRectangle(button1Pos.x, button1Pos.y, 200, 90, BLACK);

		// End 2D mode
		EndMode2D();

		// Draw score board
		DrawTexture(scoreBoard, -2, 2, RAYWHITE);

		// Draw pop-up 
		DrawTexture(popUp, 1367, 919, RAYWHITE);

		EndDrawing();
	}
}