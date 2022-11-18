#pragma once
#include <iostream>
#include <vector>
#include "raylib.h"
#include "animations.h"
#include "cityOperations.h"

#define lineColor CLITERAL(Color){ 5, 10, 23, 255 }

struct LinePoints
{
	// coordinates for line start
	Vector2 startPoint = {};

	// coordinates for line finish
	Vector2 endPoint = {};
};

// Travel to next selected city (if possible)
void travelToNextCity(Vector2 mousePoint, City* cities, City activeCity, City* tempCity, bool* searchingNextCity, bool* showPopUpMenu, int citiesCounter, int* indexPtr);

// Handle mouse input for the pop-up 
void handlePopUpInput(bool* searchingNextCity, bool* showPopUpMenu, bool* nextCityChosenPtr, City* cities, City* activeCity, City* tempCity, Rectangle confirmHitbox, Rectangle denyHitbox, int* indexPtr, PopUpAnimationFrame popUpFrame, std::vector<LinePoints>* conLinesPtr, int* travelPointsPtr, int* bonusPtr);