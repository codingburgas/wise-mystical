#include <raylib.h>
#include "cityOperations.h"

// Handle mouse input relative to the quiz optiopns
void handleQuizInput(City activeCity, Rectangle optionHitboxes[4], bool * showQuizPtr)
{
	// Chdck if the left mouse button is pressed
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
	{
		// Cycle through the option hitboxes
		for (int i = 0; i < 4; i++)
		{
			// Check for collision with the true answer
			if (CheckCollisionPointRec(Vector2(GetMousePosition()), optionHitboxes[i]) && activeCity.trueAnswer == i+1)
			{
				// Add active text update !

				// Update quiz animation status
				*showQuizPtr = false;
			}
			else if(CheckCollisionPointRec(Vector2(GetMousePosition()), optionHitboxes[i]))
			{
				// Update quiz animation status
				*showQuizPtr = false;
			}
		}
	}
}