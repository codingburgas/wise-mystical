#include <iostream>
#include "raylib.h"
#include "menu.h"
#include "timer.h"
#include "animations.h"
#include "travelLogic.h"
#include "quizLogic.h"
#include "cityOperations.h"

/**
 * Draw active city animation.
 */
void drawActiveCityAnimation(ActiveCityAnimationFrame* activeCityAnimationParts, City activeCity)
{
	// Variable to store the animations frames
	int opr = 0;

	// Update animation frame color, based on circles' radius
	for (int i = 0; i < 3; i++)
	{
		// Translate circles' radius to int 
		opr = int(activeCityAnimationParts[i].size);

		// Change the color's opacity based on the circles' radius
		switch (opr)
		{
		case 5:
			activeCityAnimationParts[i].color = frame1;
			break;
		case 7:
			activeCityAnimationParts[i].color = frame2;
			break;
		case 8:
			activeCityAnimationParts[i].color = frame3;
			break;
		case 10:
			activeCityAnimationParts[i].color = frame4;
			break;
		case 11:
			activeCityAnimationParts[i].color = frame5;
			break;
		case 12:
			activeCityAnimationParts[i].color = frame6;
			break;
		case 14:
			activeCityAnimationParts[i].color = frame7;
			break;
		case 16:
			activeCityAnimationParts[i].color = frame8;
			break;
		case 17:
			activeCityAnimationParts[i].color = frame9;
			break;
		case 19:
		case 20:
			activeCityAnimationParts[i].color = frame10;
			break;
		}
	}

	// Active city animation
	for (int i = 0; i < 3; i++)
	{
		// Draw the 3 circles
		DrawCircleV(Vector2{ activeCity.coordinates.x, activeCity.coordinates.y - float(3) }, activeCityAnimationParts[i].size, activeCityAnimationParts[i].color);

		// Check for circle radius update direction (+, -)
		if (activeCityAnimationParts[i].direction == '+')
		{
			// Upadate circle radius
			activeCityAnimationParts[i].size += float(0.07);

			// Reverse update director when radius reaches maximum(15)
			if (activeCityAnimationParts[i].size >= 20)
			{
				activeCityAnimationParts[i].direction = '-';
			}
		}

		// Check for circle radius update direction (+, -)
		if (activeCityAnimationParts[i].direction == '-')
		{
			// Upadate circle radius
			activeCityAnimationParts[i].size -= float(0.07);

			// Reverse update director when radius reaches minimum(5)
			if (activeCityAnimationParts[i].size <= 5)
			{
				activeCityAnimationParts[i].direction = '+';
			}
		}
	}
}

/**
 * Draw pop-up animation across its different states.
 */
void drawPopUpAnimationBottom(PopUpAnimationFrame* componentPtr, float endY, bool showComponent)
{
	// Check if pop-up component should be extended ot retracted 
	if (showComponent)
	{
		// Update animation state to -1(decreasing)
		componentPtr->state = -1;
	}
	else if (!showComponent)
	{
		// Update animation state to 1(increasing)
		componentPtr->state = 1;
	}

	// Update target position based on animation state
	switch (componentPtr->state)
	{
		// Update target position in decreasing state
	case -1:
		componentPtr->pos.y -= 2.5;

		// Check for top animation boundary
		if (componentPtr->pos.y <= endY)
		{
			// Snap target to boundary
			componentPtr->pos.y = endY;

			// Update animation state to 0(paused)
			componentPtr->state = 0;
		}
		break;

		// Update target position in increasing state
	case 1:
		componentPtr->pos.y += 2.5;

		// Check for bottom animation boundary
		if (componentPtr->pos.y >= 1080)
		{
			// Snap target to boundary
			componentPtr->pos.y = 1080;

			// Update animation state to 0(paused)
			componentPtr->state = 0;
		}
		break;

		// Account for the paused animation state
	default:
		break;
	}

	// Draw pop-up menu
	DrawTextureV(componentPtr->texture, componentPtr->pos, RAYWHITE);
}

/**
 * Draw pop-up animation side.
 */
void drawPopUpAnimationSide(PopUpAnimationFrame* componentPtr, Texture2D texture, float endX, bool showComponent)
{
	// Check if pop-up component should be extended ot retracted 
	if (showComponent)
	{
		// Update animation state to -1(decreasing)
		componentPtr->state = -1;
	}
	else if (!showComponent)
	{
		// Update animation state to 1(increasing)
		componentPtr->state = 1;
	}

	// Update target position based on animation state
	switch (componentPtr->state)
	{
		// Update target position in decreasing state
	case -1:
		componentPtr->pos.x -= 2.5;

		// Check for top animation boundary
		if (componentPtr->pos.x <= endX)
		{
			// Snap target to boundary
			componentPtr->pos.x = endX;

			// Update animation state to 0(paused)
			componentPtr->state = 0;
		}
		break;

		// Update target position in increasing state
	case 1:
		componentPtr->pos.x += 2.5;

		// Check for top animation boundary
		if (componentPtr->pos.x >= 1920)
		{
			// Snap target to boundary
			componentPtr->pos.x = 1920;

			// Update animation state to 0(paused)
			componentPtr->state = 0;
		}
		break;

		// Account for the paused animation state
	default:
		break;
	}

	DrawTextureV(texture, componentPtr->pos, RAYWHITE);
}

/**
 * Draw popUp buttons hover effect.
 */
void drawPopUpMenuHover(Rectangle confirmHitbox, Rectangle denyHitbox, Texture2D confirmHover, Texture2D denyHover, PopUpAnimationFrame* popUpAnimationFramePtr)
{
	// Check if pop-up is fully extended
	if (popUpAnimationFramePtr->pos.y == 913)
	{
		// Check if the mouse is hovering over the confirm button
		if (CheckCollisionPointRec(Vector2(GetMousePosition()), confirmHitbox))
		{
			// Draw confirm button hover effect
			DrawTexture(confirmHover, 1434, 985, RAYWHITE);
		}
		// Check if the mouse is hovering over the deny button
		else if (CheckCollisionPointRec(Vector2(GetMousePosition()), denyHitbox))
		{
			// Draw deny button hover effect
			DrawTexture(denyHover, 1666, 985, RAYWHITE);
		}
	}
}

/**
 * Manage warning animation.
 */
void manageWarningAnimation(Vector2 mousePoint, City cities[40], City activeCity, PopUpAnimationFrame* warningAnimationFramePtr, PopUpAnimationFrame popUpMenuFrame, Timer* warningTimerPtr, float* warningScreentimePtr, bool* wariningVisiblePtr, bool showPopUpMenu)
{
	// Check if a visited city is clicked
	for (int i = 0; i < 40; i++)
	{
		if (CheckCollisionPointRec(mousePoint, Rectangle{ cities[i].hitbox.x - (cities[i].hitbox.width / 2), cities[i].hitbox.y - (cities[i].hitbox.height / 2), cities[i].hitbox.width, cities[i].hitbox.height }))
		{
			// Check if selected city is visited
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && cities[i].name != activeCity.name && cities[i].wasVisited == true)
			{
				// Reset warning time each time a visited city is clicked
				*warningScreentimePtr = 2.5f;

				// Start up the timer with the reset screentime
				StartTimer(warningTimerPtr, *warningScreentimePtr);
			}
		}
	}

	// Tick timer
	UpdateTimer(warningTimerPtr);

	// Check if the timer hasn't expired 
	if (!TimerDone(warningTimerPtr))
	{
		// Allow the warningAlert to be drawn
		*wariningVisiblePtr = true;
	}
	else
	{
		// Restrict the drawing of the warningAlert
		*wariningVisiblePtr = false;
	}

	// Check if the pop-up menu is drawn
	if (!showPopUpMenu && popUpMenuFrame.pos.y == 1080)
	{
		// Update the warning's position if the pop-up menu is retracted
		warningAnimationFramePtr->pos.x = 1475;
	}
	else
	{
		// Keep original posion next to the pop-up menu
		warningAnimationFramePtr->pos.x = 936;
	}
}

/**
 * Draw option components.
 */
void drawOptionComponent(Option options[4], Texture2D texture, float x, float y, int index, int i)
{
	// Check for and fix minor line disposition
	if ((i == 0 || i == 1) && index != 0 && index != 25 && index != 35 && index != 30 && index != 20 && index != 10 && index != 15)
	{
		// Draw option hover effect
		DrawTextureV(texture, Vector2{ x - 2, y - 1 }, RAYWHITE);
	}
	else if (index != 0)
	{
		// Draw option hover effect
		DrawTextureV(texture, Vector2{ x - 2, y - 2 }, RAYWHITE);
	}

	// Check for and fix minor line disposition
	if (index == 0)
	{
		if (i == 0 || i == 1)
		{
			// Draw option hover effect
			DrawTextureV(texture, Vector2{ x - 5, y - 4 }, RAYWHITE);
		}
		else
		{
			// Draw option hover effect
			DrawTextureV(texture, Vector2{ x - 5, y - 5 }, RAYWHITE);
		}
	}

	// Check for and fix minor line disposition
	if (index == 25 || index == 35 || index == 30 || index == 20 || index == 10 || index == 15)
	{
		if (i == 0 || i == 1)
		{
			// Draw option hover effect
			DrawTextureV(texture, Vector2{ x - 3, y - 1 }, RAYWHITE);
		}
		else
		{
			// Draw option hover effect
			DrawTextureV(texture, Vector2{ x - 3, y - 2 }, RAYWHITE);
		}
	}
}

/**
 * Draw quiz options hover effect.
 */
void drawQuizOptionsHover(Option options[4], PopUpAnimationFrame quizAnimationFrame, int index)
{
	// Check if quiz window is fully extended
	if (quizAnimationFrame.pos.x == 956)
	{
		// Check for all 4 buttons
		for (int i = 0; i < 4; i++)
		{
			// Check for collision between the mouse pointer and the option hitbox
			if (CheckCollisionPointRec(Vector2(GetMousePosition()), options[i].hitbox))
			{
				drawOptionComponent(options, options[i].hoverEffect, options[i].hitbox.x, options[i].hitbox.y, index, i);
			}
		}
	}
}

/**
 * Draw option indicators to show if the selected option was true or false.
 */
void drawOptionIndicators(City activeCity, Option options[4], PopUpAnimationFrame quizAnimationFrame, bool optionSelected, int index)
{
	if (optionSelected)
	{
		// Check for all 4 buttons
		for (int i = 0; i < 4; i++)
		{
			// Draw indicators if the selected option was true
			if (activeCity.trueAnswer == i + 1)
			{
				switch (i)
				{
				case 0:
					drawOptionComponent(options, options[i].trueAnswerIndicator, quizAnimationFrame.pos.x + 77, quizAnimationFrame.pos.y + 802, index, i);
					break;
				case 1:
					drawOptionComponent(options, options[i].trueAnswerIndicator, quizAnimationFrame.pos.x + 77, quizAnimationFrame.pos.y + 869, index, i);
					break;
				case 2:
					drawOptionComponent(options, options[i].trueAnswerIndicator, quizAnimationFrame.pos.x + 78, quizAnimationFrame.pos.y + 937, index, i);
					break;
				case 3:
					drawOptionComponent(options, options[i].trueAnswerIndicator, quizAnimationFrame.pos.x + 77, quizAnimationFrame.pos.y + 1005, index, i);
					break;
				}
			}
			// Draw indicators if the selected option was false
			else
			{
				switch (i)
				{
				case 0:
					drawOptionComponent(options, options[i].falseAnswerIndicator, quizAnimationFrame.pos.x + 77, quizAnimationFrame.pos.y + 802, index, i);
					break;
				case 1:
					drawOptionComponent(options, options[i].falseAnswerIndicator, quizAnimationFrame.pos.x + 77, quizAnimationFrame.pos.y + 869, index, i);
					break;
				case 2:
					drawOptionComponent(options, options[i].falseAnswerIndicator, quizAnimationFrame.pos.x + 78, quizAnimationFrame.pos.y + 937, index, i);
					break;
				case 3:
					drawOptionComponent(options, options[i].falseAnswerIndicator, quizAnimationFrame.pos.x + 77, quizAnimationFrame.pos.y + 1004, index, i);
					break;
				}

			}
		}
	}
}

// Draw game info button
void drawSideButtons(Texture2D gameInfoButton, Texture2D backButton, Circle gameInfoHitbox, Circle backButtonHitbox)
{
	if (CheckCollisionPointCircle(GetMousePosition(), gameInfoHitbox.centerPos, gameInfoHitbox.radius))
	{
		DrawTexture(gameInfoButton, -87, 876, RAYWHITE);
	}
	else
	{
		DrawTexture(gameInfoButton, -97, 876, RAYWHITE);
	}

	if (CheckCollisionPointCircle(GetMousePosition(), backButtonHitbox.centerPos, backButtonHitbox.radius))
	{
		DrawTexture(backButton, -87, 980, RAYWHITE);
	}
	else
	{
		DrawTexture(backButton, -97, 980, RAYWHITE);
	}
}

// Manage game info animation
void manageSideButtonInput(GameScreen* currentScreenPtr, Circle gameInfoHitbox, Circle backButtonHitbox, bool* showGameInfoPtr, bool* drawMenuTransitionPtr)
{
	if (CheckCollisionPointCircle(GetMousePosition(), gameInfoHitbox.centerPos, gameInfoHitbox.radius) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		if (*showGameInfoPtr)
		{
			*showGameInfoPtr = false;
		}
		else
		{
			*showGameInfoPtr = true;
		}
	}

	if (CheckCollisionPointCircle(GetMousePosition(), backButtonHitbox.centerPos, backButtonHitbox.radius) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		*drawMenuTransitionPtr = true;
	}
}
