#pragma once
#include "raylib.h"

struct City {
    // Name of the city
    const char* name;

    // X and Y coordinates on the map
    Vector2 coordinates;

    // Hitbox for collision with the mouse pointer
    Rectangle hitbox;

    // Boolean for highlighting current city
    bool isActive;
};

// Initialise cities
City* intialiseCitiesArray(City cities[40]);