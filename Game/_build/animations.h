#pragma once
#include "raylib.h"
#include "menu.h"
#include "cityOperations.h"
#include "timer.h"
#include "quizLogic.h"

/**
 * Define active city animation colors.
 */
#define frame1 CLITERAL(Color){ 5, 10, 23, 120 }
#define frame2 CLITERAL(Color){ 5, 10, 23, 115 }
#define frame3 CLITERAL(Color){ 5, 10, 23, 110 }
#define frame4 CLITERAL(Color){ 5, 10, 23, 105 }
#define frame5 CLITERAL(Color){ 5, 10, 23, 100 }
#define frame6 CLITERAL(Color){ 5, 10, 23, 95 }
#define frame7 CLITERAL(Color){ 5, 10, 23, 90 }
#define frame8 CLITERAL(Color){ 5, 10, 23, 85 }
#define frame9 CLITERAL(Color){ 5, 10, 23, 80 }
#define frame10 CLITERAL(Color){ 5, 10, 23, 75 }

 /**
  * Define Active city animation frame struct.
  */
struct ActiveCityAnimationFrame {

    // circle radius
    float size;

    // radius update direction (positive, or negative)
    char direction;

    // circle color
    Color color;
};

/**
 * Define Pop up animation frame.
 */
struct PopUpAnimationFrame {

    // texture
    Texture2D texture;

    // position
    Vector2 pos;

    // -1(decreasing), 0(paused), 1(increasing)
    int state;
};

/**
 * Draw active city animation on said location on the map.
 */
void drawActiveCityAnimation(ActiveCityAnimationFrame* activeCityAnimationParts, City activeCity);

/**
 * Draw pop-up animation bottom across different states.
 */
void drawPopUpAnimationBottom(PopUpAnimationFrame* componentPtr, float endY, bool showComponent);


/**
 * Draw pop-up animation side across different states.
 */
void drawPopUpAnimationSide(PopUpAnimationFrame* componentPtr, Texture2D texture, float endX, bool showComponent);
/**
 * Draw popUp buttons hover effect .
 */
void drawPopUpMenuHover(Rectangle confirmHitbox, Rectangle denyHitbox, Texture2D confirmHover, Texture2D denyHover, PopUpAnimationFrame* popUpAnimationFramePtr);

/**
 * Manage warning animation.
 */
void manageWarningAnimation(Vector2 mousePoint, City cities[40], City activeCity, PopUpAnimationFrame* warningAnimationFramePtr, PopUpAnimationFrame popUpMenuFrame, Timer* warningTimerPtr, float* warningScreentimePtr, bool* wariningVisiblePtr, bool showPopUpMenu);

/**
 * Draw quiz options hover effect.
 */
void drawQuizOptionsHover(Option options[4], PopUpAnimationFrame quizAnimationFrame, int index);

/**
 * Draw option indicators.
 */
void drawOptionIndicators(City activeCity, Option options[4], PopUpAnimationFrame quizAnimationFrame, bool optionSelected, int index);

/**
 * Draw game info button.
 */
void drawSideButtons(Texture2D gameInfoButton, Texture2D backButton, Circle gameInfoHitbox, Circle backButtonHitbox);

/**
 * Manage game info animation.
 */
void manageSideButtonInput(GameScreen* currentScreenPtr, Circle gameInfoHitbox, Circle backButtonHitbox, bool* showGameInfoPtr, bool* drawMenuTransitionPtr);