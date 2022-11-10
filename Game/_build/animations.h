#pragma once
#include "cityOperations.h"

// Define active city animation colors
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

// Active city animation frame struct
struct activeCityAnimationFrame {

    // circle radius
    float size;

    // radius update direction (positive, or negative)
    char direction;

    // circle color
    Color color;
};

// Pop up animation frame
struct popUpAnimationFrame {

    // texture
    Texture2D texture;

    // position
    Vector2 pos;

    // -1(decreasing), 0(paused), 1(increasing)
    int state;
};

// Draw active city animation on said location on the map
void drawActiveCityAnimation(activeCityAnimationFrame* activeCityAnimationParts, City activeCity);

// Draw pop-up animation across different states
void popUpAnimation(popUpAnimationFrame* ptr2, bool showPopUpMenu);