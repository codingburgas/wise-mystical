#include <iostream>
#include "raylib.h"
#include "animations.h"
#include "cityOperations.h"

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
			activeCityAnimationParts[i].size += float(0.05);

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
			activeCityAnimationParts[i].size -= float(0.05);

			// Reverse update director when radius reaches minimum(5)
			if (activeCityAnimationParts[i].size <= 5)
			{
				activeCityAnimationParts[i].direction = '+';
			}
		}
	}
}

// Draw pop-up animation across different states
void popUpAnimation(popUpAnimationFrame* ptr2, bool showPopUpMenu)
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
		if (ptr2->pos.y <= 919)
		{
			// Snap target to boundary
			ptr2->pos.y = 919;

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
}