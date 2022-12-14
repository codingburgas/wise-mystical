#pragma once
#include <raylib.h>
#include "cityOperations.h"

struct Option
{
	// Option hitbox
	Rectangle hitbox = {};

	// Hover effect texture
	Texture hoverEffect;

	// True answer indicator
	Texture trueAnswerIndicator;

	// False answer indicator
	Texture falseAnswerIndicator;
};

// Handle mouse input relative to the quiz optiopns
void handleQuizInput(City activeCity, Option options[4], bool* showQuizPtr, bool* optionSelectedPtr, int* scorePtr, int* startNumPtr, int* endNumPtr, int* countUpstepPtr, bool* countUpDonePtr, int* bonusPtr);
