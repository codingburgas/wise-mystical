#include "City.h"

void City::setCity(const char* name, Vector2 userLocation)
{
	cityName = name;
	location = userLocation;
	land = { location.x, location.y, 15, 15 };
}

void City::drawCityLocation()
{
	DrawCircle(land.x, land.y, 15, BLACK);
}

void City::activateCity()
{
	isActive = true;
}

void City::drawName()
{
	DrawText(cityName, location.x + 15, location.y + 15, 20, BLACK);
}