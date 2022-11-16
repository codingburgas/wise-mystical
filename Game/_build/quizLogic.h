#pragma once
#include <raylib.h>
#include "cityOperations.h"

struct Option
{
	// Option hitbox
	Rectangle hitbox = {};

	// Hover effect texture
	Texture hoverEffect;
};

// Handle mouse input relative to the quiz optiopns
void handleQuizInput(City activeCity, Option optionHitboxes[4], bool* showQuizPtr);