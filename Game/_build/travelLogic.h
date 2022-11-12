#pragma once
#include <vector>
#include "raylib.h"
#include "animations.h"
#include "cityOperations.h"

struct LINEPOINTS
{
	// coordinates for line start
	Vector2 startingPoint = {};

	// coordinates for line finish
	Vector2 finishPoint = {};
};

// Travel to next selected city (if possible)
void travelToNextCity(Vector2 mousePoint, City* cities, City activeCity, City* tempCity, bool* searchingNextCity, bool* showPopUpMenu, int citiesCounter, int* indexPtr);

// Handle mouse input for the pop-up 
void handlePopUpInput(bool* searchingNextCity, bool* showPopUpMenu, City* cities, City* activeCity, City* tempCity, Rectangle confirmHitbox, Rectangle denyHitbox, int* indexPtr, popUpAnimationFrame popUpFrame, std::vector<LINEPOINTS>* conLinesPtr);