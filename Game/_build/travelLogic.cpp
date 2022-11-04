#include "raylib.h"
#include "cityOperations.h"

Vector2 goToNextCity(Vector2 mousePointer, City cityArr[40], int cityCounter)
{
	bool choosingCity = true;
	Vector2 city;

	while (choosingCity)
	{
		for (int i = 0; i < cityCounter; i++)
		{
			if (CheckCollisionPointRec(mousePointer, cityArr[i].hitbox))
			{
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					city = cityArr[i].coordinates;
					cityArr[i].isActive = true;
					choosingCity = false;
				}
			}
		}
	}

	return city;
}