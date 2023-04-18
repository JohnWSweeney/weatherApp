#include "header.h"

void currentConditions(forecastData newForecast)
{
	std::cout << "---------------------------------" << std::endl;
	std::cout << newForecast.day[0] << ", " << newForecast.month[0] << " " << newForecast.dayNum[0] << ", ";
	std::cout << newForecast.year[0] << std::endl;
	std::cout << "---------------------------------" << std::endl;
	std::cout << "Current conditions:" << std::endl;
	std::cout << newForecast.temperature[0] << "\370F, ";
	std::cout << newForecast.precipitation[0] << "% chance of precipitation" << std::endl;
	std::cout << newForecast.detailedForecast << std::endl;
}