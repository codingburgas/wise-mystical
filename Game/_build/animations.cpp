#include <iostream>
#include "raylib.h"
#include "timer.h"
#include "animations.h"
#include "travelLogic.h"
#include "quizLogic.h"
#include "cityOperations.h"

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
		DrawCircleV(Vector2{ activeCity.coordinates.x, activeCity.coordinates.y-float(3) }, activeCityAnimationParts[i].size, activeCityAnimationParts[i].color);

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

// Draw pop-up animation across its different states
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

void drawPopUpAnimationSide(PopUpAnimationFrame* quizPtr, Texture2D texture, bool showQuiz)
{
	// Check if pop-up component should be extended ot retracted 
	if (showQuiz)
	{
		// Update animation state to -1(decreasing)
		quizPtr->state = -1;
	}
	else if (!showQuiz)
	{
		// Update animation state to 1(increasing)
		quizPtr->state = 1;
	}

	// Update target position based on animation state
	switch (quizPtr->state)
	{
		// Update target position in decreasing state
	case -1:
		quizPtr->pos.x -= 2.5;

		// Check for top animation boundary
		if (quizPtr->pos.x <= 956)
		{
			// Snap target to boundary
			quizPtr->pos.x = 956;

			// Update animation state to 0(paused)
			quizPtr->state = 0;
		}
		break;

		// Update target position in increasing state
	case 1:
		quizPtr->pos.x += 2.5;

		// Check for top animation boundary
		if (quizPtr->pos.x >= 1920)
		{
			// Snap target to boundary
			quizPtr->pos.x = 1920;

			// Update animation state to 0(paused)
			quizPtr->state = 0;
		}	
		break;

		// Account for the paused animation state
	default:
		break;
	}

	DrawTextureV(texture, quizPtr->pos, RAYWHITE);
}

// Draw popUp buttons hover effect
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

// Manage warning animation 
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

// Draw quiz options hover effect
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
				// Check for and fix minor line disposition
				if ((i == 0 || i == 1) && index != 0 && index != 25 && index != 35 && index != 30 && index != 20 && index != 10 && index != 15)
				{
					// Draw option hover effect
					DrawTextureV(options[i].hoverEffect, Vector2{ options[i].hitbox.x - 2, options[i].hitbox.y - 1 }, RAYWHITE);
				}
				else if(index != 0)
				{
					// Draw option hover effect
					DrawTextureV(options[i].hoverEffect, Vector2{ options[i].hitbox.x - 2, options[i].hitbox.y - 2 }, RAYWHITE);
				}	

				// Check for and fix minor line disposition
				if (index == 0)
				{
					if (i == 0 || i == 1)
					{
						// Draw option hover effect
						DrawTextureV(options[i].hoverEffect, Vector2{ options[i].hitbox.x - 5, options[i].hitbox.y - 4 }, RAYWHITE);
					}
					else
					{
						// Draw option hover effect
						DrawTextureV(options[i].hoverEffect, Vector2{ options[i].hitbox.x - 5, options[i].hitbox.y - 5 }, RAYWHITE);
					}
				}

				// Check for and fix minor line disposition
				if (index == 25 || index == 35 || index == 30 || index == 20 || index == 10 || index == 15)
				{
					if (i == 0 || i == 1)
					{
						// Draw option hover effect
						DrawTextureV(options[i].hoverEffect, Vector2{ options[i].hitbox.x - 3, options[i].hitbox.y - 1 }, RAYWHITE);
					}
					else
					{
						// Draw option hover effect
						DrawTextureV(options[i].hoverEffect, Vector2{ options[i].hitbox.x - 3, options[i].hitbox.y - 2 }, RAYWHITE);
					}
				}
			}
		}
	}
}
