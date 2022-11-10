#include <iostream>
#include "raylib.h"
#include "game.h"
#include "animations.h"
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
	Texture2D cityMarker = LoadTexture("../resources/images/City marker.png");

	// Load font from the file structure
	Font comfortaaRegular = LoadFontEx("../resources/font/Comfortaa-Regular.ttf", 25, 0, 250);

	// Mouse position
	Vector2 mousePoint = { 0.0f, 0.0f };

	// Camera position
	float cameraPosX = float(GetScreenWidth()) / 2;
	float cameraPosY = float(GetScreenHeight()) / 2;

	// Declare game camera
	Camera2D camera = {};
	camera.offset = { float(width) / 2, float(height) / 2 };
	camera.target = { cameraPosX, cameraPosY };
	camera.zoom = 1;
	camera.rotation = 0;

	// Vector for all cities
	City cities[40];
	City* citiArrayPtr = intialiseCitiesArray(cities);
	citiArrayPtr = cities;
	
	// City variables
	const int countiesCounter = 40;
	int startCityNum = GetRandomValue(0, 39);

	// Active city variables
	City activeCity = cities[startCityNum];
	cities[startCityNum].wasVisited = true;
	City* activeCityPtr = &activeCity;

	// Temporary city variables
	int index = 0;
	int* indexPtr = &index;
	City tempCity = {};
	City *tempCityPtr = &tempCity;

	// Varibles for travel process
	bool searchingNextCity = true;
	bool* searchingNextCityPtr = &searchingNextCity;
	bool showPopUpMenu = false;
	bool* showPopUpMenuPtr = &showPopUpMenu;

	// Define variables for active city animation
	activeCityAnimationFrame activeCityAnimationParts[3] = {
		{5, '+', frame1},
		{15, '+', frame6},
		{20, '+', frame10},
	};
	activeCityAnimationFrame* activeCityAnimationPartsPtr = activeCityAnimationParts;

	// Define variables for pop up animation
	popUpAnimationFrame popUpFrame = { popUp, Vector2{ 1367, 1080 }, 0};
	popUpAnimationFrame* ptr3 = &popUpFrame;
	Rectangle confirmHitbox = { 1467, 980, 186, 67 };
	Rectangle denyHitbox = { 1697, 980, 186, 67 };

	while (!WindowShouldClose())
	{
		// Update camera position
		mousePoint = GetScreenToWorld2D({ GetMousePosition().x, GetMousePosition().y}, camera);
		camera.target = { cameraPosX, cameraPosY };

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

		// Travel to next selected city (if possible)
		travelToNextCity(mousePoint, citiArrayPtr, activeCity, tempCityPtr, searchingNextCityPtr, showPopUpMenuPtr, countiesCounter, indexPtr);

		// Handle mouse input for the pop-up 
		handlePopUpInput(searchingNextCityPtr, showPopUpMenuPtr, cities, activeCityPtr, tempCityPtr, confirmHitbox, denyHitbox, indexPtr);

		BeginDrawing();
		
		// Set background color for the framebuffer 
		ClearBackground(mapBackgroundColor);

		// Begin 2D mode
		BeginMode2D(camera);

		// Draw the map on the screen
		DrawTextureEx(map, Vector2{ 0,0 }, 0, 1, mapColor);

		// Mark the current active city mark
		drawActiveCityAnimation(activeCityAnimationPartsPtr, activeCity);

		// Draw city markers on the map
		drawCityLandmarks(citiArrayPtr, 40, comfortaaRegular, cityMarker);	

		// End 2D mode
		EndMode2D();

		// Draw score board
		DrawTexture(scoreBoard, -2, 2, RAYWHITE);

		// Draw pop-up animation across different states
		popUpAnimation(ptr3, showPopUpMenu);

		// Draw pop-up 
		DrawTextureV(popUp, popUpFrame.pos, RAYWHITE);
		
		EndDrawing();
	}
}