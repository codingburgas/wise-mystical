#include <iostream>
#include <vector>
#include <math.h>
#include "raylib.h"
#include "game.h"
#include "movement.h"
#include "timer.h"
#include "animations.h"
#include "cityOperations.h"
#include "travelLogic.h"
#include "updateActiveText.h"

void startGame()
{
	int width = 1920;
	int height = 1080;

	InitWindow(width, height, "Game");

	// Load font from the file structure
	Font comfortaaRegular = LoadFontEx("../resources/font/Comfortaa-Regular.ttf", 25, 0, 250);

	// Load map components texture from the file structure
	Texture2D map = LoadTexture("../resources/images/map components/map.png");	
	Texture2D cityMarker = LoadTexture("../resources/images/map components/City marker.png");

	// Load UI components from the file structure
	Texture2D scoreBoard = LoadTexture("../resources/images/UI components/Score board.png");
	Texture2D popUpMenu = LoadTexture("../resources/images/UI components/Travel pop-up.png");
	Texture2D visitedCityWarning = LoadTexture("../resources/images/UI components/City warning.png");
	Texture2D confirmHover = LoadTexture("../resources/images/UI components/Confirm hover.png");
	Texture2D denyHover = LoadTexture("../resources/images/UI components/Deny hover.png");

	// Mouse position
	Vector2 mousePoint = { 0.0f, 0.0f };

	// Camera position
	float cameraPosX = 0;
	float* cameraPosXPtr = &cameraPosX;
	float cameraPosY = 0;
	float* cameraPosYPtr = &cameraPosY;

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
	const int cityCounter = 40;
	int startCityNum = GetRandomValue(0, 39);

	// Vector for gameplay path
	std::vector<LinePoints> conLines;
	std::vector<LinePoints>* conLinesPtr = &conLines;

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
	ActiveCityAnimationFrame activeCityAnimationParts[3] = {
		{5, '+', frame1},
		{15, '+', frame6},
		{20, '+', frame10},
	};
	ActiveCityAnimationFrame* activeCityAnimationPartsPtr = activeCityAnimationParts;

	// Define variables for pop-up menu animation
	PopUpAnimationFrame popUpMenuFrame = { popUpMenu, Vector2{ 1347, 1080 }, 0};
	PopUpAnimationFrame* popUpMenuFramePtr = &popUpMenuFrame;
	Rectangle confirmHitbox = { 1462, 993, 186, 67 };
	Rectangle denyHitbox = { 1693, 993, 186, 67 };
	
	// Define variables for warning pop up animation
	PopUpAnimationFrame warningAnimationFrame = { visitedCityWarning, Vector2{ 936, 1080 }, 0 };
	PopUpAnimationFrame* warningAnimationFramePtr = &warningAnimationFrame;
	bool wariningVisible = false;
	bool* warningVisiblePtr = &wariningVisible;

	// Variables for warning timer
	float warningScreentime = 2.5f;
	float* warningScreentimePtr = &warningScreentime;
	Timer warningTimer = { 0 };
	Timer* warningTimerPtr = &warningTimer;

	// Define active text variables
	std::string popUpText = "";

	// Set initail camera target
	setInitialCameraPos(cameraPosXPtr, cameraPosYPtr, startCityNum);

	while (!WindowShouldClose())
	{
		// Update target
		mousePoint = GetScreenToWorld2D({ GetMousePosition().x, GetMousePosition().y}, camera);
		camera.target = { *cameraPosXPtr, *cameraPosYPtr };

		// Update the camera's position based on keyboard input
		updateCameraPos(cameraPosXPtr, cameraPosYPtr);

		// Travel to next selected city (if possible)
		travelToNextCity(mousePoint, citiArrayPtr, activeCity, tempCityPtr, searchingNextCityPtr, showPopUpMenuPtr, cityCounter, indexPtr);

		// Handle mouse input for the pop-up 
		handlePopUpInput(searchingNextCityPtr, showPopUpMenuPtr, cities, activeCityPtr, tempCityPtr, confirmHitbox, denyHitbox, indexPtr, popUpMenuFrame, conLinesPtr);

		BeginDrawing();
		
		// Set background color for the framebuffer 
		ClearBackground(mapBackgroundColor);

		// Begin 2D mode
		BeginMode2D(camera);

		// Draw the map on the screen
		DrawTextureEx(map, Vector2{ 0,0 }, 0, 1, mapColor);

		// Draw travel pathway
		for (LinePoints &n : conLines)
		{
			// Draw line outer layer
			DrawLineEx(n.startPoint, n.endPoint, 10, WHITE);

			// Draw line inner layer
			DrawLineEx(n.startPoint, n.endPoint, 7, lineColor);	
		}

		// Mark the current active city mark
		drawActiveCityAnimation(activeCityAnimationPartsPtr, activeCity);

		// Draw city markers on the map
		drawCityLandmarks(citiArrayPtr, 40, comfortaaRegular, cityMarker);

		// End 2D mode
		EndMode2D();

		// Draw score board
		DrawTexture(scoreBoard, -2, 2, RAYWHITE);

		// Draw pop-up menu animation across different states
		drawPopUpAnimation(popUpMenu, popUpMenuFramePtr, 913, showPopUpMenu);

		// Draw popUp buttons hover effect 
		drawPopUpMenuHover(confirmHitbox, denyHitbox, confirmHover, denyHover, popUpMenuFramePtr);

		// Update pop-up menu active text
		if (popUpMenuFrame.pos.y == 1080 || popUpMenuFrame.pos.y == 913)
		{
			popUpText = updatePopUpActiveText(popUpText, activeCity, tempCity);
		}
		
		// Draw pop-up menu active text
		DrawTextEx(comfortaaRegular, popUpText.c_str(), Vector2{ 1439, popUpMenuFrame.pos.y + float(19) }, 25, 1, WHITE);

		// Manage warning animation 
		manageWarningAnimation(mousePoint, cities, activeCity, warningAnimationFramePtr, popUpMenuFrame, warningTimerPtr, warningScreentimePtr, warningVisiblePtr, showPopUpMenu);

		// Draw warning animation across its different states
		drawPopUpAnimation(visitedCityWarning, warningAnimationFramePtr, 990, wariningVisible);
		
		EndDrawing();
	}
}