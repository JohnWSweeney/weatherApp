#include "header.h"

int main()
{
	std::cout << "weatherApp v0.0.0" << std::endl;

	float lat, lon;
	std::string currentDirectory = getCoordinates(&lat, &lon);
	std::string stationFilepath = getStation(lat, lon, currentDirectory);
	getForecasts(stationFilepath, currentDirectory);

	forecastData newForecast;
	newForecast = hourlyForecastExtractor(currentDirectory, newForecast);
	newForecast = forecastExtractor(currentDirectory, newForecast);
	currentConditions(newForecast);

	system("pause");
}