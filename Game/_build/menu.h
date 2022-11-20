#pragma once
#include "raylib.h"

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