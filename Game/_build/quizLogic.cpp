#include <raylib.h>
#include "animations.h"
#include "cityOperations.h"
#include "quizLogic.h"
#include "timer.h"

// Handle mouse input relative to the quiz optiopns
void handleQuizInput(City activeCity, Option options[4], bool * showQuizPtr)
{
	// Chdck if the left mouse button is pressed
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
	{
		// Cycle through the option hitboxes
		for (int i = 0; i < 4; i++)
		{
			// Check for collision with the true answer
			if (CheckCollisionPointRec(Vector2(GetMousePosition()), options[i].hitbox) && activeCity.trueAnswer == i+1)
			{
				// Add active text update !

				// Update quiz animation status
				*showQuizPtr = false;
			}
			else if(CheckCollisionPointRec(Vector2(GetMousePosition()), options[i].hitbox))
			{
				// Update quiz animation status
				*showQuizPtr = false;
			}
		}
	}
}