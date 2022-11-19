#include <raylib.h>
#include "animations.h"
#include "cityOperations.h"
#include "quizLogic.h"
#include "timer.h"

// Handle mouse input relative to the quiz optiopns
void handleQuizInput(City activeCity, Option options[4], bool* showQuizPtr, bool* optionSelectedPtr, int* scorePtr, int* startNumPtr, int* endNumPtr, int* countUpstepPtr, bool* countUpDonePtr, int* bonusPtr)
{
	// Chdck if the left mouse button is pressed
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		// Cycle through the option hitboxes
		for (int i = 0; i < 4; i++)
		{
			// Check for collision with the true answer
			if (CheckCollisionPointRec(Vector2(GetMousePosition()), options[i].hitbox) && activeCity.trueAnswer == i + 1)
			{
				if (*showQuizPtr == true)
				{
					// Update score and count up sequence variables
					*startNumPtr = *scorePtr;
					*scorePtr += 200 + *bonusPtr;
					*endNumPtr = *scorePtr;
					*countUpDonePtr = false;
					*countUpstepPtr = (*endNumPtr - *startNumPtr) / 100;
				}

				*optionSelectedPtr = true;
				*showQuizPtr = false;

			}
			else if (CheckCollisionPointRec(Vector2(GetMousePosition()), options[i].hitbox))
			{
				*optionSelectedPtr = true;
				*showQuizPtr = false;
			}
		}
	}
}