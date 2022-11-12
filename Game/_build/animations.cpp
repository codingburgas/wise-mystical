#include <iostream>
#include "raylib.h"
#include "animations.h"
#include "cityOperations.h"

// Start or restart a timer with a specific lifetime
void StartTimer(Timer* timer, float lifetime)
{
	if (timer != NULL)
	{
		timer->Lifetime = lifetime;
	}
}

// Update a timer with the current frame time
void UpdateTimer(Timer* timer)
{
	// Subtract this frame from the timer if it's not allready expired
	if (timer != NULL && timer->Lifetime > 0)
	{
		timer->Lifetime -= GetFrameTime();
	}
}

// Check if a timer is done
bool TimerDone(Timer* timer)
{
	if (timer != NULL)
	{
		return timer->Lifetime <= 0;
	}

	return false;
}

void drawActiveCityAnimation(activeCityAnimationFrame* activeCityAnimationParts, City activeCity)
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
void drawPopUpMenuAnimation(Texture2D popUpMenu,popUpAnimationFrame* ptr2, bool showPopUpMenu)
{
	// Check for mouse input and update animation state 
	if (showPopUpMenu)
	{
		// Update animation state to -1(decreasing)
		ptr2->state = -1;
	}
	else if (!showPopUpMenu)
	{
		// Update animation state to 1(increasing)
		ptr2->state = 1;
	}

	// Update target position based on animation state
	switch (ptr2->state)
	{
	// Update target position in decreasing state
	case -1:
		ptr2->pos.y -= 2.5;

		// Check for top animation boundary
		if (ptr2->pos.y <= 913)
		{
			// Snap target to boundary
			ptr2->pos.y = 913;

			// Update animation state to 0(paused)
			ptr2->state = 0;
		}
		break;

	// Update target position in increasing state
	case 1:
		ptr2->pos.y += 2.5;

		// Check for bottom animation boundary
		if (ptr2->pos.y >= 1080)
		{
			// Snap target to boundary
			ptr2->pos.y = 1080;

			// Update animation state to 0(paused)
			ptr2->state = 0;
		}
		break;

	// Account for the paused animation state
	default:
		break;
	}

	// Draw pop-up menu
	DrawTextureV(popUpMenu, ptr2->pos, RAYWHITE);
}

// Draw popUp buttons hover effect
void drawPopUpMenuHover(Rectangle confirmHitbox, Rectangle denyHitbox, Texture2D confirmHover, Texture2D denyHover, popUpAnimationFrame* popUpAnimationFramePtr)
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
void manageWarningAnimation(Vector2 mousePoint, City cities[40], City activeCity, popUpAnimationFrame* warningAnimationFramePtr, Timer* warningTimerPtr, float* warningScreentimePtr, bool* wariningVisiblePtr, bool showPopUpMenu)
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
	if (!showPopUpMenu)
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

// Draw warning animation across its different states
void drawWarningAnimation(Texture2D warning, popUpAnimationFrame* warningAnimationFramePtr, bool wariningVisible)
{
	// Check for mouse input and update animation state 
	if (wariningVisible)
	{
		// Update animation state to -1(decreasing)
		warningAnimationFramePtr->state = -1;
	}
	else if (!wariningVisible)
	{
		// Update animation state to 1(increasing)
		warningAnimationFramePtr->state = 1;
	}

	// Update target position based on animation state
	switch (warningAnimationFramePtr->state)
	{
	// Update target position in decreasing state
	case -1:
		warningAnimationFramePtr->pos.y -= 2.5;

		// Check for top animation boundary
		if (warningAnimationFramePtr->pos.y <= 990)
		{
			// Snap target to boundary
			warningAnimationFramePtr->pos.y = 990;

			// Update animation state to 0(paused)
			warningAnimationFramePtr->state = 0;
		}
		break;

	// Update target position in increasing state
	case 1:
		warningAnimationFramePtr->pos.y += 2.5;

		// Check for bottom animation boundary
		if (warningAnimationFramePtr->pos.y >= 1080)
		{
			// Snap target to boundary
			warningAnimationFramePtr->pos.y = 1080;

			// Update animation state to 0(paused)
			warningAnimationFramePtr->state = 0;
		}
		break;

	// Account for the paused animation state
	default:
		break;
	}

	// Draw visited city warning
	DrawTextureV(warning, warningAnimationFramePtr->pos, RAYWHITE);
}