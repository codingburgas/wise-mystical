#pragma once
#include <string>
#include "raylib.h"
#include "cityOperations.h"
#include "travelLogic.h"

// Update the pop-up active text
std::string updatePopUpActiveText(std::string text, City activeCity, City tempCity, PopUpAnimationFrame popUpMenuFrame);

// Update score count up sequence
void updateScoreCountUp(bool* countUpDone, int* startNum, int* endNum, int countUpstep);

// Draw travel points count
void drawtravelPointsCount(Font comfortaaTravelPoints, int travelPoints);
