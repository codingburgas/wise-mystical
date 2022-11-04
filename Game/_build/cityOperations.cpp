#include <iostream>
#include <string>
#include <vector>
#include "raylib.h"
#include "cityOperations.h"

City* intialiseCitiesArray(City cities[40])
{
	float hitboxWidth = 10;
	float hitboxHeight = 10;

	for (int i = 0; i < 40; i++)
	{
		switch (i)
		{
		case 0:
			cities[i] = { "Reykjavik", Vector2{185, 355}, Rectangle{185,355,hitboxWidth,hitboxHeight}, false };
			break;
		case 1:
			cities[i] = { "Oslo", Vector2{1240, 940}, Rectangle{1240,940,hitboxWidth,hitboxHeight}, false };
			break;
		case 2:
			cities[i] = { "Stockholm",Vector2{1540, 970}, Rectangle{1540,970,hitboxWidth,hitboxHeight}, false };
			break;
		case 3:
			cities[i] = { "Tallinn",Vector2{1800, 920}, Rectangle{1800,920,hitboxWidth,hitboxHeight}, false };
			break;
		case 4:
			cities[i] = { "Riga",Vector2{1810, 1100}, Rectangle{1810,1100,hitboxWidth,hitboxHeight}, false };
			break;
		case 5:
			cities[i] = { "Vilnius",Vector2{1890, 1270}, Rectangle{1890,1270,hitboxWidth,hitboxHeight}, false };
			break;
		case 6:
			cities[i] = { "Copenhagen",Vector2{1330, 1270}, Rectangle{1330,1270,hitboxWidth,hitboxHeight}, false };
			break;
		case 7:
			cities[i] = { "Edinburg",Vector2{670, 1200}, Rectangle{670,1200,hitboxWidth,hitboxHeight}, false };
			break;
		case 8:
			cities[i] = { "Dublin",Vector2{470, 1360}, Rectangle{470,1360,hitboxWidth,hitboxHeight}, false };
			break;
		case 9:
			cities[i] = { "Hamburg",Vector2{1215, 1440}, Rectangle{1215,1440,hitboxWidth,hitboxHeight}, false };
			break;
		case 10:
			cities[i] = { "Minsk",Vector2{2020, 1340}, Rectangle{2020,1340,hitboxWidth,hitboxHeight}, false };
			break;
		case 11:
			cities[i] = { "Warsaw",Vector2{1730, 1495}, Rectangle{1730,1495,hitboxWidth,hitboxHeight}, false };
			break;
		case 12:
			cities[i] = { "Berlin",Vector2{1360, 1510}, Rectangle{1360,1510,hitboxWidth,hitboxHeight}, false };
			break;
		case 13:
			cities[i] = { "Amsterdam",Vector2{980, 1520}, Rectangle{980,1520,hitboxWidth,hitboxHeight}, false };
			break;
		case 14:
			cities[i] = { "London",Vector2{735, 1560}, Rectangle{735,1560,hitboxWidth,hitboxHeight}, false };
			break;
		case 15:
			cities[i] = { "Paris",Vector2{830, 1760}, Rectangle{830,1760,hitboxWidth,hitboxHeight}, false };
			break;
		case 16:
			cities[i] = { "Brussels",Vector2{940, 1630}, Rectangle{940,1630,hitboxWidth,hitboxHeight}, false };
			break;
		case 17:
			cities[i] = { "Prague",Vector2{1415, 1715}, Rectangle{1415,1715,hitboxWidth,hitboxHeight}, false };
			break;
		case 18:
			cities[i] = { "Krakòw",Vector2{1670, 1690}, Rectangle{1670,1690,hitboxWidth,hitboxHeight}, false };
			break;
		case 19:
			cities[i] = { "Budapest",Vector2{1690, 1890}, Rectangle{1690,1890,hitboxWidth,hitboxHeight}, false };
			break;
		case 20:
			cities[i] = { "Vienna",Vector2{1545, 1845}, Rectangle{1545,1845,hitboxWidth,hitboxHeight}, false };
			break;
		case 21:
			cities[i] = { "Munich",Vector2{1305, 1875}, Rectangle{1305,1875,hitboxWidth,hitboxHeight}, false };
			break;
		case 22:
			cities[i] = { "Zagreb",Vector2{1525, 2055}, Rectangle{1525,2055,hitboxWidth,hitboxHeight}, false };
			break;
		case 23:
			cities[i] = { "Belgrade",Vector2{1790, 2080}, Rectangle{1790,2080,hitboxWidth,hitboxHeight}, false };
			break;
		case 24:
			cities[i] = { "Bucharest",Vector2{2095, 2050}, Rectangle{2095,2050,hitboxWidth,hitboxHeight}, false };
			break;
		case 25:
			cities[i] = { "Nessebar",Vector2{2210, 2165}, Rectangle{2210,2165,hitboxWidth,hitboxHeight}, false };
			break;
		case 26:
			cities[i] = { "Veliko Tarnovo",Vector2{2130, 2160}, Rectangle{2130,2160,hitboxWidth,hitboxHeight}, false };
			break;
		case 27:
			cities[i] = { "Sarajevo",Vector2{1680, 2155}, Rectangle{1680,2155,hitboxWidth,hitboxHeight}, false };
			break;
		case 28:
			cities[i] = { "Florence",Vector2{1290, 2205}, Rectangle{1290,2205,hitboxWidth,hitboxHeight}, false };
			break;
		case 29:
			cities[i] = { "Marseille",Vector2{960, 2230}, Rectangle{960,2230,hitboxWidth,hitboxHeight}, false };
			break;
		case 30:
			cities[i] = { "Rome",Vector2{1360, 2345}, Rectangle{1360,2345,hitboxWidth,hitboxHeight}, false };
			break;
		case 31:
			cities[i] = { "Lisbon",Vector2{50, 2445}, Rectangle{50,2445,hitboxWidth,hitboxHeight}, false };
			break;
		case 32:
			cities[i] = { "Madrid",Vector2{405, 2410}, Rectangle{405,2410,hitboxWidth,hitboxHeight}, false };
			break;
		case 33:
			cities[i] = { "Barcelona",Vector2{765, 2355}, Rectangle{765,2355,hitboxWidth,hitboxHeight}, false };
			break;
		case 34:
			cities[i] = { "Cagliari",Vector2{1165, 2545}, Rectangle{1165,2545,hitboxWidth,hitboxHeight}, false };
			break;
		case 35:
			cities[i] = { "Palerno",Vector2{1415, 2635}, Rectangle{1415,2635,hitboxWidth,hitboxHeight}, false };
			break;
		case 36:
			cities[i] = { "Helsinki",Vector2{1765, 865}, Rectangle{1765,865,hitboxWidth,hitboxHeight}, false };
			break;
		case 37:
			cities[i] = { "Ioannina",Vector2{1870, 2465}, Rectangle{1870,2465,hitboxWidth,hitboxHeight}, false };
			break;
		case 38:
			cities[i] = { "Athens",Vector2{2065, 2575}, Rectangle{2065,2575,hitboxWidth,hitboxHeight}, false };
			break;
		case 39:
			cities[i] = { "Istanbul",Vector2{2315, 2275}, Rectangle{2315,2275,hitboxWidth,hitboxHeight}, false };
			break;
		}
	}

	return cities;
}