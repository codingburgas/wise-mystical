#pragma once
#include <raylib.h>
#include "cityOperations.h"

// Handle mouse input relative to the quiz optiopns
void handleQuizInput(City activeCity, Rectangle optionHitboxes[4], bool* showQuizPtr);