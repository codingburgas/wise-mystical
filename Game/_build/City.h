#pragma once
#include "raylib.h"

class City
{
private:
	const char* cityName;
public:
	Rectangle land;
	Vector2 location;
	bool isActive = false;

	void setCity(const char* name, Vector2 userLocation);

	void drawCityLocation();

	void activateCity();

	void drawName();
};