#include <iostream>
#include <string>
#include <cmath>
#include "raylib.h"
#include "cityOperations.h"
#include "animations.h"

// Update the pop-up active text
std::string updatePopUpActiveText(std::string text, City activeCity, City tempCity, PopUpAnimationFrame popUpMenuFrame)
{
	// Reset the active text 
	text = "";

	// Update the active text with the current information
	text.append("Travel from ");
	text.append(activeCity.name);
	text.append(" to ");
	text.append(tempCity.name);
	if (popUpMenuFrame.pos.y == 913)
	{
		text.append("?");
	}

	// Return the updated active text
	return text;
}

// Update score count up sequence
void updateScoreCountUp(bool* countUpDone, int* startNum, int* endNum, int countUpstep)
{
	// Update score count up
	*startNum += countUpstep;

	// Check for new score boundary
	if (*startNum >= *endNum)
	{
		*startNum = *endNum;
		*countUpDone = true;
	}
}

// Draw travel points count
void drawtravelPointsCount(Font comfortaaTravelPoints, int travelPoints)
{
	float x = 0;

	// Check for travel points count and update x to center the counter
	if (travelPoints >= 20 )
	{
		x += 2;
		if (travelPoints / 10 % 10 == 1)
		{
			x += 6;
		}
	}
	else if (travelPoints < 20 && travelPoints >= 10)
	{
		if (travelPoints / 10 % 10 == 1)
		{
			x += 6;
		}
	}
	else if (travelPoints < 10) 
	{
		x += 13;
		if (travelPoints / 10 % 10 == 1)
		{
			x += 6;
		}
	}

	// Draw travel points counter
	DrawTextEx(comfortaaTravelPoints, TextFormat("%i", travelPoints), Vector2{ float(283.84) + x, 242 }, 40, 1, WHITE);
}