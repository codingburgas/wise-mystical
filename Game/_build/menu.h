#pragma once
#include "raylib.h"
#include "game.h"

struct menuButton {

    Texture2D button;

    Texture2D hoverEffect;
};

/**
* Define Circle
*/
struct Circle {

    // circle center positon
    Vector2 centerPos;

    // circle radius
    float radius = 0;
};

/**
 * Draw menu buttons.
 */
void drawMenuButtons(Circle menuHitboxes[3], menuButton menuButtons[3]);

/**
 * Handle menu input.
 */
void hangleMenuInput(GameScreen* currentScreenPtr, Circle menuHitboxes[3], bool* quitButtonPressedPtr);