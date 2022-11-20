#pragma once
#include "raylib.h"
#include "game.h"

#define transitiopnColor CLITERAL(Color){ 5, 10, 23, 255 }

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

struct TransitionFrame {

    // circle center positon
    Vector2 centerPos;

    // circle radius
    float radius = 0;

    int state = 0;
};

/**
 * Draw menu buttons.
 */
void drawMenuButtons(Circle menuHitboxes[3], menuButton menuButtons[3]);

/**
 * Handle menu input.
 */
void hangleMenuInput(Circle menuHitboxes[3], TransitionFrame* transitionPtr, bool* quitButtonPressedPtr, bool* drawMenuTransitionPtr, bool* showGameInfoPtr, bool* showMenuPtr);

/**
* Draw transition animation.
*/
void drawTransition(TransitionFrame* transitionPtr, bool* drawMenuTransitionPtr);