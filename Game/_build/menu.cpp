#include "raylib.h"
#include "game.h"
#include "menu.h"

/**
 * Draw menu buttons.
 */
void drawMenuButtons(Circle menuHitboxes[3], menuButton menuButtons[3])
{
	for (int i = 0; i < 3; i++)
	{
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
void hangleMenuInput(GameScreen* currentScreenPtr, Circle menuHitboxes[3], bool* quitButtonPressedPtr)
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
				*currentScreenPtr = GAMEPLAY;
				break;
			case 1:
				// Show about
				break;
			// Close game
			case 2:
				*quitButtonPressedPtr = true;
				break;
			}
		}
	}
}