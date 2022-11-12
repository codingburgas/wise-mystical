#include <iostream>
#include <vector>
#include "raylib.h"
#include "game.h"
#include "animations.h"
#include "cityOperations.h"
#include "travelLogic.h"
#include "updateActiveText.h"

void startGame()
{
	int width = 1920;
	int height = 1080;

	InitWindow(width, height, "Game");

	// Load map texture from the file structure
	Texture2D map = LoadTexture("../resources/images/map.png");	

	// Load font from the file structure
	Font comfortaaRegular = LoadFontEx("../resources/font/Comfortaa-Regular.ttf", 25, 0, 250);

	// Load UI from the file structure
	Texture2D scoreBoard = LoadTexture("../resources/images/Score board.png");
	Texture2D popUpMenu = LoadTexture("../resources/images/Travel pop-up.png");
	Texture2D visitedCityWarning = LoadTexture("../resources/images/City warning.png");
	Texture2D confirmHover = LoadTexture("../resources/images/Confirm hover.png");
	Texture2D denyHover = LoadTexture("../resources/images/Deny hover.png");
	Texture2D cityMarker = LoadTexture("../resources/images/City marker.png");

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

	// Vector for gameplay path
	std::vector<LINEPOINTS> conLines;
	std::vector<LINEPOINTS>* conLinesPtr = &conLines;

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

	// Define variables for pop-up menu animation
	popUpAnimationFrame popUpMenuFrame = { popUpMenu, Vector2{ 1347, 1080 }, 0};
	popUpAnimationFrame* popUpMenuFramePtr = &popUpMenuFrame;
	Rectangle confirmHitbox = { 1462, 993, 186, 67 };
	Rectangle denyHitbox = { 1693, 993, 186, 67 };

	// Define variables for warning pop up animation
	popUpAnimationFrame warningAnimationFrame = { visitedCityWarning, Vector2{ 936, 1080 }, 0 };
	popUpAnimationFrame* warningAnimationFramePtr = &warningAnimationFrame;
	bool wariningVisible = false;
	bool* warningVisiblePtr = &wariningVisible;

	// Variables for warning timer
	float warningScreentime = 2.5f;
	float* warningScreentimePtr = &warningScreentime;
	Timer warningTimer = { 0 };
	Timer* warningTimerPtr = &warningTimer;

	// Define active text variables
	std::string popUpText = "";

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
		handlePopUpInput(searchingNextCityPtr, showPopUpMenuPtr, cities, activeCityPtr, tempCityPtr, confirmHitbox, denyHitbox, indexPtr, popUpMenuFrame, conLinesPtr);

		BeginDrawing();
		
		// Set background color for the framebuffer 
		ClearBackground(mapBackgroundColor);

		// Begin 2D mode
		BeginMode2D(camera);

		// Draw the map on the screen
		DrawTextureEx(map, Vector2{ 0,0 }, 0, 1, mapColor);

		// Under development
		/*for (LINEPOINTS n : conLines)
		{
			DrawLineEx(n.startingPoint, n.finishPoint, 5, BLACK);
		}*/

		// Mark the current active city mark
		drawActiveCityAnimation(activeCityAnimationPartsPtr, activeCity);

		// Draw city markers on the map
		drawCityLandmarks(citiArrayPtr, 40, comfortaaRegular, cityMarker);

		// End 2D mode
		EndMode2D();

		// Draw score board
		DrawTexture(scoreBoard, -2, 2, RAYWHITE);

		// Draw pop-up animation across different states
		drawPopUpMenuAnimation(popUpMenu, popUpMenuFramePtr, showPopUpMenu);

		// Draw popUp buttons hover effect 
		drawPopUpMenuHover(confirmHitbox, denyHitbox, confirmHover, denyHover, popUpMenuFramePtr);

		// Update pop-up menu active text
		if (popUpMenuFrame.pos.y == 1080 || popUpMenuFrame.pos.y == 913)
		{
			popUpText = updatePopUpActiveText(popUpText, activeCity, tempCity);
		}
		
		// Draw pop-up menu active text
		DrawTextEx(comfortaaRegular, popUpText.c_str(), Vector2{ 1439, popUpMenuFrame.pos.y + float(19) }, 25, 1, WHITE);

		manageWarningAnimation(mousePoint, cities, activeCity, warningAnimationFramePtr, warningTimerPtr, warningScreentimePtr, warningVisiblePtr, showPopUpMenu);

		drawWarningAnimation(visitedCityWarning, warningAnimationFramePtr, wariningVisible);
		
		EndDrawing();
	}
}