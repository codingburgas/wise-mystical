#include <iostream>
#include <vector>
#include <math.h>
#include "raylib.h"
#include "menu.h"
#include "game.h"
#include "movement.h"
#include "timer.h"
#include "animations.h"
#include "cityOperations.h"
#include "travelLogic.h"
#include "quizLogic.h"
#include "manageActiveText.h"

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

	// Load game GUI components from the file structure
	Texture2D scoreBoard = LoadTexture("../resources/images/UI components/Score board.png");
	Texture2D popUpMenu = LoadTexture("../resources/images/UI components/Travel pop-up.png");
	Texture2D visitedCityWarning = LoadTexture("../resources/images/UI components/City warning.png");
	Texture2D confirmHover = LoadTexture("../resources/images/UI components/Confirm hover.png");
	Texture2D denyHover = LoadTexture("../resources/images/UI components/Deny hover.png");
	
	// Load menu components from the file structure
	Texture2D menu = LoadTexture("../resources/images/UI components/menu components/menu.png");
	menuButton menuButtons[3] = {
		{LoadTexture("../resources/images/UI components/menu components/buttons/play button.png"), LoadTexture("../resources/images/UI components/menu components/hover effects/play button hover.png")},
		{LoadTexture("../resources/images/UI components/menu components/buttons/about button.png"), LoadTexture("../resources/images/UI components/menu components/hover effects/about button hover.png")},
		{LoadTexture("../resources/images/UI components/menu components/buttons/quit button.png"), LoadTexture("../resources/images/UI components/menu components/hover effects/quit button hover.png")}
	};

	// Define menu button hitboxes
	Circle menuHitboxes[3] = {
		{Vector2{ 606.5, 142.5 }, 90 },
		{Vector2{ 450.5, 431.5 }, 90 },
		{Vector2{ 170.5, 597.5 }, 90 }
	};

	// Load game info components from the file structure
	Texture2D gameInfo = LoadTexture("../resources/images/UI components/game info.png");
	Texture2D gameInfoButton = LoadTexture("../resources/images/UI components/game info button.png");
	Circle gameInfoHitbox = { Vector2{41, 1038}, 49};

	// Define menu transition animation variables
	TransitionFrame transition = { Vector2{float(GetScreenWidth() / 2), float(GetScreenHeight() / 2)}, 1 };
	TransitionFrame* transitionPtr = &transition;
	bool drawMenuTransition = false;
	bool* drawMenuTransitionPtr = &drawMenuTransition;
	bool menuUnloaded = false;

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

	// Declare screen variable
	GameScreen currentScreen = MENU;
	GameScreen* currentScreenPtr = &currentScreen;
	bool quitButtonPressed = false;
	bool* quitButtonPressedPtr = &quitButtonPressed;

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
	bool optionSelected = false;
	bool* optionSelectedPtr = &optionSelected;
	Option options[4] = {
		{{1034, 800, 740, 51}, LoadTexture("../resources/images/UI components/option hover/option a hover.png"), LoadTexture("../resources/images/UI components/option indicators/Right answer a.png"), LoadTexture("../resources/images/UI components/option indicators/Wrong answer a.png")},
		{{1034, 867, 740, 51}, LoadTexture("../resources/images/UI components/option hover/option b hover.png"), LoadTexture("../resources/images/UI components/option indicators/Right answer b.png"), LoadTexture("../resources/images/UI components/option indicators/Wrong answer b.png")},
		{{1034, 934, 740, 51}, LoadTexture("../resources/images/UI components/option hover/option c hover.png"), LoadTexture("../resources/images/UI components/option indicators/Right answer c.png"), LoadTexture("../resources/images/UI components/option indicators/Wrong answer c.png")},
		{{1034, 1001, 740, 51}, LoadTexture("../resources/images/UI components/option hover/option d hover.png"), LoadTexture("../resources/images/UI components/option indicators/Right answer d.png"), LoadTexture("../resources/images/UI components/option indicators/Wrong answer d.png")}
	};

	// Initial quiz timer
	bool intialTimerStarted = false;
	float freeTime = 1.8;
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

	// Define variables for game info window
	PopUpAnimationFrame gameInfoAnimationFrame = { gameInfo , Vector2{1920, -2}, 0 };
	PopUpAnimationFrame* gameInfoAnimationFramePtr = &gameInfoAnimationFrame;
	bool showGameInfo = false;
	bool* showGameInfoPtr = &showGameInfo;

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
	/*ToggleFullscreen();*/

	while (!WindowShouldClose())
	{
		// Switch between gamemodes for drawing
		switch (currentScreen)
		{
		case MENU:
		{
			hangleMenuInput(menuHitboxes, transitionPtr, quitButtonPressedPtr, drawMenuTransitionPtr, showGameInfoPtr);
		} break;

		case GAMEPLAY:
		{
			if (transition.radius <= 10 && !intialTimerStarted)
			{
				// Start initial free timer countdown
				StartTimer(&freeTimeTimer, freeTime);
				intialTimerStarted = true;
			}

			// Unload menu when it's not needed
			if (currentScreen == GAMEPLAY && !menuUnloaded)
			{
				for (int i = 0; i < 3; i++)
				{
					UnloadTexture(menuButtons[i].button);
					UnloadTexture(menuButtons[i].hoverEffect);
				}

				UnloadTexture(menu);
				menuUnloaded = true;
			}

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
			handlePopUpInput(citiArrayPtr, activeCityPtr, tempCityPtr, popUpMenuFrame, confirmHitbox, denyHitbox, conLinesPtr, searchingNextCityPtr, showPopUpMenuPtr, nextCityChosenPtr, indexPtr, travelPointsPtr, bonusPtr);

			// Update count up sequence
			updateScoreCountUp(countUpDonePtr, startNumPtr, endNumPtr, countUpstep);

			// Manage warning animation 
			manageWarningAnimation(mousePoint, cities, activeCity, warningAnimationFramePtr, popUpMenuFrame, warningTimerPtr, warningScreentimePtr, warningVisiblePtr, showPopUpMenu);

			// Update initial free timer countdown
			UpdateTimer(&freeTimeTimer);

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
				handleQuizInput(activeCity, options, showQuizPtr, optionSelectedPtr, scorePtr, startNumPtr, endNumPtr, countUpstepPtr, countUpDonePtr, bonusPtr);

				// Reset the selected option check
				if (quizAnimationFrame.pos.x == 1920)
				{
					optionSelected = false;
				}
			}

		} break;

		default: break;
		}

		BeginDrawing();

		// Set background color for the framebuffer 
		ClearBackground(mapBackgroundColor);

		// Switch gamemode
		if (transitionPtr->radius >= 1120)
		{
			currentScreen = GAMEPLAY;
			quitButtonPressed = false;
		}

		// Switch between gamemodes for drawing
		switch (currentScreen)
		{
		case MENU:
		{
			DrawTexture(menu, 0, 0, RAYWHITE);

			drawMenuButtons(menuHitboxes, menuButtons);

			for (int i = 0; i < 5; i++)
			{
				// Draw game info
				drawPopUpAnimationSide(gameInfoAnimationFramePtr, gameInfo, 918, showGameInfo);
			}
		} break;

		case GAMEPLAY:
		{
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
			drawCityMarkers(citiArrayPtr, activeCity, cityMarkers, cityCounter);

			// Draw city names
			drawCityNames(citiArrayPtr, 40, comfortaa);

			// End 2D mode
			EndMode2D();

			// Draw score board
			DrawTexture(scoreBoard, -2, 2, RAYWHITE);

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

			// Draw travel points count
			drawTravelPointsCount(comfortaaTravelPoints, travelPoints);

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

			// Draw warning animation across its different states
			drawPopUpAnimationBottom(warningAnimationFramePtr, 990, wariningVisible);

			// Manage quiz texture loading, unloading and drawing
			if (nextCityChosen)
			{
				// Make animation 5 times faster
				for (int i = 0; i < 5; i++)
				{
					// Draw pop-up animation side across different states
					drawPopUpAnimationSide(quizPtr, activeQuiz, 956, showQuiz);
				}

				if (!optionSelected)
				{
					// Draw quiz options hover effect
					drawQuizOptionsHover(options, quizAnimationFrame, index);
				}

				// Draw option indicators to show if the selected option was true or false
				drawOptionIndicators(activeCity, options, quizAnimationFrame, optionSelected, index);
			}

			// Draw game info button
			drawGameInfoButton(gameInfoButton, gameInfoHitbox);

			// Manage game info animation
			mamageGameInfoWindowAnimation(gameInfoHitbox, showGameInfoPtr);

			for (int i = 0; i < 5; i++)
			{
				// Draw game info
				drawPopUpAnimationSide(gameInfoAnimationFramePtr, gameInfo, 918, showGameInfo);
			}

		} break;

		default: break;
		}

		// Draw transition animation
		for (int i = 0; i < 10; i++)
		{
			drawTransition(transitionPtr, drawMenuTransitionPtr);
		}

		EndDrawing();

		// Close game if quit button is pressed
		if (quitButtonPressed && transition.radius == 0)
		{
			CloseWindow();
		}
	}
}