#include <vector>
#include "raylib.h"
#include "cityOperations.h"
#include "travelLogic.h"
#include "animations.h"

// Travel to next selected city (if possible)
void travelToNextCity(Vector2 mousePoint, City *cities, City activeCity, City *tempCity, bool *searchingNextCity, bool *showPopUpMenu, int citiesCounter, int *indexPtr)
{
	// Check if travel is allowed
	if (searchingNextCity)
	{
		for (int i = 0; i < citiesCounter; i++)
		{
			// Check for collision between a city's marker and the mouse pointer
			if (CheckCollisionPointRec(mousePoint, Rectangle{ cities[i].hitbox.x - (cities[i].hitbox.width / 2), cities[i].hitbox.y - (cities[i].hitbox.height / 2), cities[i].hitbox.width, cities[i].hitbox.height }))
			{
				// Check if selected city is available for travel
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && cities[i].name != activeCity.name && cities[i].wasVisited == false)
				{
					// Store the index of the selected city
					*indexPtr = i;

					// Update the temporary city's value
					*tempCity = cities[i];

					// Temporary restrict travel
					*searchingNextCity = false;

					// Extent pop-up
					*showPopUpMenu = true;
				}
			}
		}
	}
}

// Handle mouse input for the pop-up 
void handlePopUpInput(bool* searchingNextCity, bool* showPopUpMenu, City* cities, City* activeCity, City* tempCity, Rectangle confirmHitbox, Rectangle denyHitbox, int* indexPtr, PopUpAnimationFrame popUpFrame, std::vector<LinePoints>* conLinesPtr)
{
	// Check if confirm was clicked
	if (showPopUpMenu && CheckCollisionPointRec(Vector2(GetMousePosition()), confirmHitbox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		// Retract the pop-up
		*showPopUpMenu = false;

		// Allow travel to other selected cities
		*searchingNextCity = true;

		// Restrict further access to selected city
		cities[*indexPtr].wasVisited = true;

		// Add next set of start and end line points
		conLinesPtr->push_back({ activeCity->coordinates, tempCity->coordinates, activeCity->coordinates, 0, 0, false});

		// Upadate the active city 
		*activeCity = *tempCity;

		// Reset the temporary city 
		*tempCity = {};
	}
	// Check if deny was clicked
	else if (showPopUpMenu && CheckCollisionPointRec(Vector2(GetMousePosition()), denyHitbox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		// Retract the pop-up
		*showPopUpMenu = false;

		// Allow travel to other selected cities
		*searchingNextCity = true;

		// Reset the temporary city 
		*tempCity = {};
	}
}