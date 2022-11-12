#include <iostream>
#include <string>
#include "raylib.h"
#include "cityOperations.h"

// Update the pop-up active text
std::string updatePopUpActiveText(std::string text, City activeCity, City tempCity)
{
	// Reset the active text 
	text = "";

	// Update the active text with the current information
	text.append("Travel from ");
	text.append(activeCity.name);
	text.append(" to ");
	text.append(tempCity.name);

	// Return the updated active text
	return text;
}