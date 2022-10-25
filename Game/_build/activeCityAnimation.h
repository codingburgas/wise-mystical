#pragma once

// Define active city animation colors
#define frame1 CLITERAL(Color){ 0, 0, 0, 120 }
#define frame2 CLITERAL(Color){ 0, 0, 0, 115 }
#define frame3 CLITERAL(Color){ 0, 0, 0, 110 }
#define frame4 CLITERAL(Color){ 0, 0, 0, 105 }
#define frame5 CLITERAL(Color){ 0, 0, 0, 100 }
#define frame6 CLITERAL(Color){ 0, 0, 0, 95 }
#define frame7 CLITERAL(Color){ 0, 0, 0, 90 }
#define frame8 CLITERAL(Color){ 0, 0, 0, 85 }
#define frame9 CLITERAL(Color){ 0, 0, 0, 80 }
#define frame10 CLITERAL(Color){ 0, 0, 0, 75 }

// Active city animation frame struct
struct animationFrame {

    // circle radius
    float size;

    // radius update direction (positive, or negative)
    char direction;

    // circle color
    Color color;
};

// Draw active city animation on said location on the map
void drawActiveCityAnimation(animationFrame* activeCityAnimationParts, Vector2 activeCityCoords);