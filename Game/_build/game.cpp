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
#include "quizLogic.h"
#include "updateActiveText.h"


void startGame()
{
	int width = 1920;
	int height = 1080;

	InitWindow(width, height, "Game");

	// Load font variants from the file structure
	Font comfortaa = LoadFontEx("../resources/font/Comfortaa-Regular.ttf", 25, 0, 250);
	Font comfortaaScore = LoadFontEx("../resources/font/Comfortaa-Regular.ttf", 32, 0, 250);
	Font comfortaaTravelPoints = LoadFontEx("../resources/font/Comfortaa-Bold.ttf", 40, 0, 250);

	// Load map components texture from the file structure
	Texture2D map = LoadTexture("../resources/images/map components/map.png");
	Texture2D cityMarkers[3] = {
		LoadTexture("../resources/images/map components/City marker Easy.png"),
		LoadTexture("../resources/images/map components/City marker Medium.png"),
		LoadTexture("../resources/images/map components/City marker Hard.png")
	};

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

	// Active city variables
	City activeCity = cities[startCityNum];
	cities[startCityNum].wasVisited = true;
	City* activeCityPtr = &activeCity;

	// Temporary city variables
	City tempCity = {};
	City* tempCityPtr = &tempCity;
	int index = startCityNum;
	int* indexPtr = &index;

	// Vector for gameplay path
	std::vector<LinePoints> conLines;
	std::vector<LinePoints>* conLinesPtr = &conLines;

	// Varibles for travel process
	bool searchingNextCity = false;
	bool* searchingNextCityPtr = &searchingNextCity;
	bool showPopUpMenu = false;
	bool* showPopUpMenuPtr = &showPopUpMenu;

	// Define variables for pop-up menu animation
	PopUpAnimationFrame popUpMenuFrame = { popUpMenu, Vector2{ 1347, 1080 }, 0 };
	PopUpAnimationFrame* popUpMenuFramePtr = &popUpMenuFrame;
	Rectangle confirmHitbox = { 1462, 993, 186, 67 };
	Rectangle denyHitbox = { 1693, 993, 186, 67 };

	// Define variables for active city animation
	ActiveCityAnimationFrame activeCityAnimationParts[3] = {
		{5, '+', frame1},
		{15, '+', frame6},
		{20, '+', frame10},
	};
	ActiveCityAnimationFrame* activeCityAnimationPartsPtr = activeCityAnimationParts;

	// Define variables for quizzes
	Texture2D activeQuiz = LoadTexture("");
	Texture2D* activeQuizPtr = &activeQuiz;
	PopUpAnimationFrame quizAnimationFrame = { activeQuiz, Vector2{1920, 2}, 0 };
	PopUpAnimationFrame* quizPtr = &quizAnimationFrame;
	bool activeQuizLoaded = false;
	bool* activeQuizLoadedPtr = &activeQuizLoaded;
	bool showQuiz = false;
	bool* showQuizPtr = &showQuiz;
	bool nextCityChosen = true;
	bool* nextCityChosenPtr = &nextCityChosen;
	Option options[4] = {
		{{1034, 800, 740, 51}, LoadTexture("../resources/images/UI components/option hover/option a hover.png")},
		{{1034, 867, 740, 51}, LoadTexture("../resources/images/UI components/option hover/option b hover.png")},
		{{1034, 934, 740, 51}, LoadTexture("../resources/images/UI components/option hover/option c hover.png")},
		{{1034, 1001, 740, 51}, LoadTexture("../resources/images/UI components/option hover/option d hover.png")}
	};

	// Initial quiz timer
	float freeTime = 1.5f;
	Timer freeTimeTimer = { 0 };
	Timer* freeTimeTimerPtr = &freeTimeTimer;

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
	int score = 0;
	int* scorePtr = &score;
	int bonus = 0;
	int* bonusPtr = &bonus;
	int travelPoints = 40;
	int* travelPointsPtr = &travelPoints;

	// Define variables for score count up
	int startNum = 0;
	int* startNumPtr = &startNum;
	int endNum = 0;
	int* endNumPtr = &endNum;
	int countUpstep = 0;
	int* countUpstepPtr = &countUpstep;
	bool countUpDone = true;
	bool* countUpDonePtr = &countUpDone;

	// Set initail camera target
	setInitialCameraPos(cameraPosXPtr, cameraPosYPtr, startCityNum);

	// Start initial free timer countdown
	StartTimer(&freeTimeTimer, freeTime);

	// Put the game into fullscreen mode
	ToggleFullscreen();

	while (!WindowShouldClose())
	{
		// Update target
		mousePoint = GetScreenToWorld2D({ GetMousePosition().x, GetMousePosition().y }, camera);
		camera.target = { *cameraPosXPtr, *cameraPosYPtr };

		// Update the camera's position based on keyboard input
		updateCameraPos(cameraPosXPtr, cameraPosYPtr);

		// Travel to next selected city (if possible)
		if (quizAnimationFrame.pos.x == 1920 && !showQuiz)
		{
			travelToNextCity(mousePoint, citiArrayPtr, activeCity, tempCityPtr, searchingNextCityPtr, showPopUpMenuPtr, cityCounter, indexPtr);
		}

		// Update city travel cost and bonus
		updateCityTravelCostAndBonus(cities, activeCity, cityCounter);

		// Handle mouse input for the pop-up 
		handlePopUpInput(searchingNextCityPtr, showPopUpMenuPtr, nextCityChosenPtr, cities, activeCityPtr, tempCityPtr, confirmHitbox, denyHitbox, indexPtr, popUpMenuFrame, conLinesPtr, travelPointsPtr, bonusPtr);

		BeginDrawing();

		// Set background color for the framebuffer 
		ClearBackground(mapBackgroundColor);

		// Begin 2D mode
		BeginMode2D(camera);

		// Draw the map on the screen
		DrawTextureEx(map, Vector2{ 0,0 }, 0, 1, mapColor);

		// Draw travel pathway
		for (LinePoints& n : conLines)
		{
			// Draw line outer layer
			DrawLineEx(n.startPoint, n.endPoint, 10, WHITE);

			// Draw line inner layer
			DrawLineEx(n.startPoint, n.endPoint, 7, lineColor);
		}

		// Mark the current active city mark
		drawActiveCityAnimation(activeCityAnimationPartsPtr, activeCity);

		// Draw city markers based of distance from active city
		updateCityTravelCostAndBonus(citiArrayPtr, activeCity, cityMarkers, cityCounter);

		// Draw city names
		drawCityNames(citiArrayPtr, 40, comfortaa);

		// End 2D mode
		EndMode2D();

		// Draw score board
		DrawTexture(scoreBoard, -2, 2, RAYWHITE);

		// Update count up sequence
		updateScoreCountUp(countUpDonePtr, startNumPtr, endNumPtr, countUpstep);

		// Check for score count up
		if (countUpDone)
		{
			// Draw normal score
			DrawTextEx(comfortaaScore, TextFormat("%i", score), Vector2{ 86,31 }, 32, 1, WHITE);
		}
		else if (!countUpDone)
		{
			// Draw count up with updated value
			DrawTextEx(comfortaaScore, TextFormat("%i", startNum), Vector2{ 86,31 }, 32, 1, WHITE);
		}

		// Draw active city name
		DrawTextEx(comfortaaScore, activeCity.name.c_str(), Vector2{ 86, 108 }, 32, 1, WHITE);

		// Draw visited cities counter
		DrawTextEx(comfortaaScore, TextFormat("%i / 40", conLines.size() + 1), Vector2{ 86, 180 }, 32, 1, WHITE);

		// Draw travel points counter
		DrawTextEx(comfortaaTravelPoints, TextFormat("%i", travelPoints), Vector2{ float(283.84), 242 }, 40, 1, WHITE);

		// Draw pop-up menu animation across different states
		drawPopUpAnimationBottom(popUpMenuFramePtr, 913, showPopUpMenu);

		// Draw popUp buttons hover effect 
		drawPopUpMenuHover(confirmHitbox, denyHitbox, confirmHover, denyHover, popUpMenuFramePtr);

		// Update pop-up menu active text
		if (popUpMenuFrame.pos.y == 1080 || popUpMenuFrame.pos.y == 913)
		{
			popUpText = updatePopUpActiveText(popUpText, activeCity, tempCity, popUpMenuFrame);
		}

		// Draw pop-up menu active text
		DrawTextEx(comfortaa, popUpText.c_str(), Vector2{ 1427, popUpMenuFrame.pos.y + float(19) }, 25, 1, WHITE);

		// Manage warning animation 
		manageWarningAnimation(mousePoint, cities, activeCity, warningAnimationFramePtr, popUpMenuFrame, warningTimerPtr, warningScreentimePtr, warningVisiblePtr, showPopUpMenu);

		// Draw warning animation across its different states
		drawPopUpAnimationBottom(warningAnimationFramePtr, 990, wariningVisible);

		// Update initial free timer countdown
		UpdateTimer(&freeTimeTimer);

		// Manage quiz texture loading, unloading and drawing
		if (nextCityChosen)
		{
			// Manage quiz texture loading
			if (!activeQuizLoaded && popUpMenuFrame.pos.y == 1080 && !showPopUpMenu && TimerDone(&freeTimeTimer))
			{
				activeQuiz = LoadTexture(activeCity.textureFilePath);
				activeQuizLoaded = true;
				showQuiz = true;
			}

			//Manage quiz texture unloading
			if (quizAnimationFrame.pos.x == 1920 && !showQuiz && !searchingNextCity)
			{
				searchingNextCity = true;
				UnloadTexture(activeQuiz);
				activeQuizLoaded = false;
			}

			// Handle mouse input relative to the quiz optiopns
			handleQuizInput(activeCity, options, showQuizPtr, scorePtr, startNumPtr, endNumPtr, countUpstepPtr, countUpDonePtr, bonusPtr);

			// Make animation 5 times faster
			for (int i = 0; i < 5; i++)
			{
				// Draw pop-up animation side across different states
				drawPopUpAnimationSide(quizPtr, activeQuiz, showQuiz);
			}

			// Draw quiz options hover effect
			drawQuizOptionsHover(options, quizAnimationFrame, index);
		}

		EndDrawing();
	}
}