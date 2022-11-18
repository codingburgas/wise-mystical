#pragma once
#include <string>
#include "raylib.h"

struct City {
    // Name of the city
    std::string name = "";

    // X and Y coordinates on the map
    Vector2 coordinates = {};

    // Hitbox for collision with the mouse pointer
    Rectangle hitbox = {};

    // Visited city indicator
    bool wasVisited = false;

    // True answer variable
    int trueAnswer = 0;

    // Texture file path
    const char* textureFilePath = "";

    // Travel cost
    int travelCost = 0;

    // Bonus score
    int bonus = 0;
};

// Initialise cities
City* intialiseCitiesArray(City cities[40]);

// Draw city marks on the map
void drawCityNames(City* cities, int citiesCounter, Font comfortaaRegular);

// Draw city markers based of distance from active city
void updateCityTravelCostAndBonus(City* cities, City activeCity, Texture2D markers[3], int citiesCounter);

// Update city travel cost and bonus
void updateCityTravelCostAndBonus(City* cities, City activeCity, int citiesCounter);