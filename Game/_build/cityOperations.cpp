#include <iostream>
#include <string>
#include "raylib.h"
#include "cityOperations.h"

// Initialise cities
City* intialiseCitiesArray(City cities[40])
{
	float hitboxWidth = 15, hitboxHeight = 20;
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	// Categories:  Name:	      Position:           Rectangle Hitbox:     Hitbox:                     VCI:  TA:  Texture File Path:                                      //
	cities[0] =  { "Reykjavik",  Vector2{185,  355},  Rectangle{185,  355,  hitboxWidth, hitboxHeight}, false,  1, "../resources/images/quizzes/Quiz window Reykjavik.png" };
	cities[1] =  { "Oslo",       Vector2{1240, 940},  Rectangle{1240, 940,  hitboxWidth, hitboxHeight}, false,  3, "../resources/images/quizzes/Quiz window Oslo.png"      };
	cities[2] =  { "Stockholm",  Vector2{1540, 970},  Rectangle{1540, 970,  hitboxWidth, hitboxHeight}, false,  4, "../resources/images/quizzes/Quiz window Stockholm.png" };
	cities[3] =  { "Tallinn",    Vector2{1800, 920},  Rectangle{1800, 920,  hitboxWidth, hitboxHeight}, false,  2, "../resources/images/quizzes/Quiz window Tallinn.png"   };
	cities[4] =  { "Riga",       Vector2{1810, 1100}, Rectangle{1810, 1100, hitboxWidth, hitboxHeight}, false,  1, "../resources/images/quizzes/Quiz window Riga.png"      };
	cities[5] =  { "Vilnius",    Vector2{1890, 1270}, Rectangle{1890, 1270, hitboxWidth, hitboxHeight}, false,  4, "../resources/images/quizzes/Quiz window Vilnius.png"   };
	cities[6] =  { "Copenhagen", Vector2{1330, 1270}, Rectangle{1330, 1270, hitboxWidth, hitboxHeight}, false,  1, "../resources/images/quizzes/Quiz window Copenhagen.png"};
	cities[7] =  { "Edinburg",   Vector2{670,  1200}, Rectangle{670,  1200, hitboxWidth, hitboxHeight}, false,  3, "../resources/images/quizzes/Quiz window Edinburg.png"  };
	cities[8] =  { "Dublin",     Vector2{470,  1360}, Rectangle{470,  1360, hitboxWidth, hitboxHeight}, false,  3, "../resources/images/quizzes/Quiz window Dublin.png"    };
	cities[9] =  { "Hamburg",    Vector2{1215, 1440}, Rectangle{1215, 1440, hitboxWidth, hitboxHeight}, false,  3, "../resources/images/quizzes/Quiz window Hamburg.png"   };
	cities[10] = { "Minsk",      Vector2{2020, 1340}, Rectangle{2020, 1340, hitboxWidth, hitboxHeight}, false,  2, "../resources/images/quizzes/Quiz window Minsk.png"     };
	cities[11] = { "Warsaw",     Vector2{1730, 1495}, Rectangle{1730, 1495, hitboxWidth, hitboxHeight}, false,  1, "../resources/images/quizzes/Quiz window Warsaw.png"    };
	cities[12] = { "Berlin",     Vector2{1360, 1510}, Rectangle{1360, 1510, hitboxWidth, hitboxHeight}, false,  2, "../resources/images/quizzes/Quiz window Berlin.png"    };
	cities[13] = { "Amsterdam",  Vector2{980,  1520}, Rectangle{980,  1520, hitboxWidth, hitboxHeight}, false,  3, "../resources/images/quizzes/Quiz window Amsterdam.png" };
	cities[14] = { "London",     Vector2{735,  1560}, Rectangle{735,  1560, hitboxWidth, hitboxHeight}, false,  4, "../resources/images/quizzes/Quiz window London.png"    };
	cities[15] = { "Paris",      Vector2{830,  1760}, Rectangle{830,  1760, hitboxWidth, hitboxHeight}, false,  3, "../resources/images/quizzes/Quiz window Paris.png"     };
	cities[16] = { "Brussels",   Vector2{940,  1630}, Rectangle{940,  1630, hitboxWidth, hitboxHeight}, false,  1, "../resources/images/quizzes/Quiz window Brussels.png"  };
	cities[17] = { "Prague",     Vector2{1415, 1715}, Rectangle{1415, 1715, hitboxWidth, hitboxHeight}, false,  4, "../resources/images/quizzes/Quiz window Prague.png"    };
	cities[18] = { "Krakow",     Vector2{1670, 1690}, Rectangle{1670, 1690, hitboxWidth, hitboxHeight}, false,  3, "../resources/images/quizzes/Quiz window Krakow.png"    };
	cities[19] = { "Budapest",   Vector2{1690, 1890}, Rectangle{1690, 1890, hitboxWidth, hitboxHeight}, false,  2, "../resources/images/quizzes/Quiz window Budapest.png"  };
	cities[20] = { "Vienna",     Vector2{1545, 1845}, Rectangle{1545, 1845, hitboxWidth, hitboxHeight}, false,  3, "../resources/images/quizzes/Quiz window Vienna.png"    };
	cities[21] = { "Munich",     Vector2{1305, 1875}, Rectangle{1305, 1875, hitboxWidth, hitboxHeight}, false,  2, "../resources/images/quizzes/Quiz window Munich.png"    };
	cities[22] = { "Zagreb",     Vector2{1525, 2055}, Rectangle{1525, 2055, hitboxWidth, hitboxHeight}, false,  1, "../resources/images/quizzes/Quiz window Zagreb.png"    };
	cities[23] = { "Belgrade",   Vector2{1790, 2080}, Rectangle{1790, 2080, hitboxWidth, hitboxHeight}, false,  3, "../resources/images/quizzes/Quiz window Belgrade.png"  };
	cities[24] = { "Buchapest",  Vector2{2095, 2050}, Rectangle{2095, 2050, hitboxWidth, hitboxHeight}, false,  4, "../resources/images/quizzes/Quiz window Buchapest.png" };
	cities[25] = { "Nessebar",   Vector2{2210, 2165}, Rectangle{2210, 2165, hitboxWidth, hitboxHeight}, false,  4, "../resources/images/quizzes/Quiz window Nessebar.png"  };
	cities[26] = { "Sofia",      Vector2{1980, 2230}, Rectangle{1980, 2230, hitboxWidth, hitboxHeight}, false,  3, "../resources/images/quizzes/Quiz window Sofia.png"     };
	cities[27] = { "Sarajevo",   Vector2{1680, 2155}, Rectangle{1680, 2155, hitboxWidth, hitboxHeight}, false,  4, "../resources/images/quizzes/Quiz window Sarajevo.png"  };
	cities[28] = { "Florence",   Vector2{1290, 2205}, Rectangle{1290, 2205, hitboxWidth, hitboxHeight}, false,  2, "../resources/images/quizzes/Quiz window Florence.png"  };
	cities[29] = { "Marseille",  Vector2{960,  2230}, Rectangle{960,  2230, hitboxWidth, hitboxHeight}, false,  2, "../resources/images/quizzes/Quiz window Marseille.png" };
	cities[30] = { "Rome",       Vector2{1360, 2345}, Rectangle{1360, 2345, hitboxWidth, hitboxHeight}, false,  1, "../resources/images/quizzes/Quiz window Rome.png"      };
	cities[31] = { "Lisbon",     Vector2{50,   2445}, Rectangle{50,   2445, hitboxWidth, hitboxHeight}, false,  4, "../resources/images/quizzes/Quiz window Lisbon.png"    };
	cities[32] = { "Madrid",     Vector2{405,  2410}, Rectangle{405,  2410, hitboxWidth, hitboxHeight}, false,  2, "../resources/images/quizzes/Quiz window Madrid.png"    };
	cities[33] = { "Barcelona",  Vector2{765,  2355}, Rectangle{765,  2355, hitboxWidth, hitboxHeight}, false,  1, "../resources/images/quizzes/Quiz window Barcelona.png" };
	cities[34] = { "Cagliari",   Vector2{1165, 2545}, Rectangle{1165, 2545, hitboxWidth, hitboxHeight}, false,  1, "../resources/images/quizzes/Quiz window Cagliari.png"  };
	cities[35] = { "Palermo",    Vector2{1415, 2635}, Rectangle{1415, 2635, hitboxWidth, hitboxHeight}, false,  2, "../resources/images/quizzes/Quiz window Palermo.png"   };
	cities[36] = { "Helsinki",   Vector2{1765, 865},  Rectangle{1765, 865,  hitboxWidth, hitboxHeight}, false,  1, "../resources/images/quizzes/Quiz window Helsinki.png"  };
	cities[37] = { "Ioannina",   Vector2{1870, 2465}, Rectangle{1870, 2465, hitboxWidth, hitboxHeight}, false,  4, "../resources/images/quizzes/Quiz window Ioannina.png"  };
	cities[38] = { "Athens",     Vector2{2065, 2575}, Rectangle{2065, 2575, hitboxWidth, hitboxHeight}, false,  4, "../resources/images/quizzes/Quiz window Athens.png"    };
	cities[39] = { "Istanbul",   Vector2{2315, 2275}, Rectangle{2315, 2275, hitboxWidth, hitboxHeight}, false,  1, "../resources/images/quizzes/Quiz window Istanbul.png"  };
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------//

	// Return intialised array
	return cities;
}

// Draw city marks on the map
void drawCityLandmarks(City* cities, int citiesCounter, Font comfortaaRegular, Texture2D cityMarker)
{
	for (int i = 0; i < citiesCounter; i++)
	{
		// Draw cities hitboxes
		DrawTextureV(cityMarker, Vector2{ cities[i].hitbox.x - float(cityMarker.width / 2), cities[i].hitbox.y - float(cityMarker.height / 2) }, RAYWHITE);

		// Draw city names
		DrawTextEx(comfortaaRegular, cities[i].name.c_str(), Vector2{cities[i].coordinates.x + 7,cities[i].coordinates.y + 7}, (float)comfortaaRegular.baseSize, 1, WHITE);
	}
}