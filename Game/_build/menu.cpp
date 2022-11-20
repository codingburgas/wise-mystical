#include "raylib.h"
#include "game.h"
#include "menu.h"

/**
 * Draw menu buttons.
 */
void drawMenuButtons(Circle menuHitboxes[3], menuButton menuButtons[3])
{
	// Draw all 3 buttons
	for (int i = 0; i < 3; i++)
	{
		// Draw button effect
		if (CheckCollisionPointCircle(GetMousePosition(), menuHitboxes[i].centerPos, menuHitboxes[i].radius))
		{
			switch (i)
			{
			case 0:
				DrawTexture(menuButtons[i].hoverEffect, 514 + 10, 50 + 2, RAYWHITE);
				break;
			case 1:
				DrawTexture(menuButtons[i].hoverEffect, 358 + 6, 339 + 6, RAYWHITE);
				break;
			case 2:
				DrawTexture(menuButtons[i].hoverEffect, 80 + 2, 507 + 10, RAYWHITE);
				break;
			}
		}
		// Draw normal buttons
		else
		{
			switch (i)
			{
			case 0:
				DrawTexture(menuButtons[i].button, 514, 50, RAYWHITE);
				break;
			case 1:
				DrawTexture(menuButtons[i].button, 358, 339, RAYWHITE);
				break;
			case 2:
				DrawTexture(menuButtons[i].button, 80, 507, RAYWHITE);
				break;
			}
		}
	}
}

/**
 * Handle menu input.
 */
void hangleMenuInput(Circle menuHitboxes[3], TransitionFrame* transitionPtr, bool* quitButtonPressedPtr, bool* drawMenuTransitionPtr, bool* showGameInfoPtr, bool* showMenuPtr)
{
	//Check for mouse collison with the menu buttons
	for (int i = 0; i < 3; i++)
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointCircle(GetMousePosition(), menuHitboxes[i].centerPos, menuHitboxes[i].radius))
		{
			switch (i)
			{
				// Switch screen to GAMEPLAY
			case 0:
				*drawMenuTransitionPtr = true;
				*showMenuPtr = false;
				break;
				// Show game info
			case 1:
				if (*showGameInfoPtr == true)
				{
					*showGameInfoPtr = false;
				}
				else
				{
					*showGameInfoPtr = true;
				}
				break;
				// Close game
			case 2:
				*quitButtonPressedPtr = true;
				break;
			}
		}
	}
}

/**
* Draw transition animation.
*/
void drawTransition(TransitionFrame* transitionPtr, bool* drawMenuTransitionPtr)
{
	// Check if pop-up component should be extended ot retracted 
	if (*drawMenuTransitionPtr)
	{
		// Update animation state to -1(decreasing)
		transitionPtr->state = 1;
	}
	else if (!*drawMenuTransitionPtr)
	{
		// Update animation state to 1(increasing)
		transitionPtr->state = -1;
	}

	// Update target position based on animation state
	switch (transitionPtr->state)
	{
		// Update target position in decreasing state
	case 1:
		transitionPtr->radius += 1;

		// Check for top animation boundary
		if (transitionPtr->radius >= 1120)
		{
			// Snap target to boundary
			transitionPtr->radius = 1120;

			*drawMenuTransitionPtr = false;
		}
		break;

		// Update target position in increasing state
	case -1:
		transitionPtr->radius -= 1;

		// Check for top animation boundary
		if (transitionPtr->radius <= 0)
		{
			// Snap target to boundary
			transitionPtr->radius = 0;

			// Update animation state to 0(paused)
			transitionPtr->state = 0;
		}
		break;

		// Account for the paused animation state
	default:
		break;
	}

	// Draw circles
	DrawCircleV(transitionPtr->centerPos, transitionPtr->radius, WHITE);
	DrawCircleV(transitionPtr->centerPos, transitionPtr->radius - 1, transitiopnColor);
}