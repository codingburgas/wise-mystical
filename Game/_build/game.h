#pragma once

// Initialize new type
typedef enum GameScreen { MENU, GAMEPLAY, RESULT } GameScreen;

// Define custom background color
#define mapBackgroundColor CLITERAL(Color){ 56, 140, 233, 255 }

// Define custom map tint color
#define mapColor CLITERAL(Color){ 166, 210, 179, 255 }

// Start game
void startGame();