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

    bool wasVisited = false;
};

// Initialise cities
City* intialiseCitiesArray(City cities[40]);

// Draw city marks on the map
void drawCityLandmarks(City* cities, int citiesCounter, Font comfortaaRegular, Texture2D cityMarker);