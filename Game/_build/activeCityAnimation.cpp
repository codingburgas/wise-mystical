#include "raylib.h"
#include "activeCityAnimation.h"
#include <iostream>

void drawActiveCityAnimation(animationFrame* activeCityAnimationParts, Vector2 activeCityCoords)
{
	// Variable to store the animations frames
	int opr = 0;

	// Update animation frame color, based on circles' radius
	for (int i = 0; i < 3; i++)
	{
		// Translate circles' radius to int 
		opr = int(activeCityAnimationParts[i].size);
		switch (opr)
		{
		case 5:
			activeCityAnimationParts[i].color = frame1;
			break;
		case 6:
			activeCityAnimationParts[i].color = frame2;
			break;
		case 7:
			activeCityAnimationParts[i].color = frame3;
			break;
		case 8:
			activeCityAnimationParts[i].color = frame4;
			break;
		case 9:
			activeCityAnimationParts[i].color = frame5;
			break;
		case 10:
			activeCityAnimationParts[i].color = frame6;
			break;
		case 11:
			activeCityAnimationParts[i].color = frame7;
			break;
		case 12:
			activeCityAnimationParts[i].color = frame8;
			break;
		case 13:
			activeCityAnimationParts[i].color = frame9;
			break;
		case 14:
		case 15:
			activeCityAnimationParts[i].color = frame10;
			break;
		}
	}

	// Active city animation
	for (int i = 0; i < 3; i++)
	{
		// Draw the 3 circles
		DrawCircleV(Vector2{ activeCityCoords.x, activeCityCoords.y }, activeCityAnimationParts[i].size, activeCityAnimationParts[i].color);

		// Check for circle radius update direction (+, -)
		if (activeCityAnimationParts[i].direction == '+')
		{
			// Upadate circle radius
			activeCityAnimationParts[i].size += float(0.05);

			// Reverse update director when radius reaches maximum(15)
			if (activeCityAnimationParts[i].size >= 15)
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