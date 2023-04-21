#include "header.h"

void newForecast()
{
	std::cout << std::endl;
	float lat, lon;
	std::string currentDirectory = getCoordinates(&lat, &lon);
	std::string stationFilepath = getStation(lat, lon, currentDirectory);
	getForecasts(stationFilepath, currentDirectory);

	forecastData newForecast;
	newForecast = hourlyForecastExtractor(currentDirectory, newForecast);
	newForecast = forecastExtractor(currentDirectory, newForecast);
	int index = currentConditions(newForecast);
	fiveDayForecast(newForecast, index);
}

void start()
{
	newForecast();
	bool running = true;
	while (running)
	{
		std::cout << std::endl;
		std::cout << "Would you like a new forecast? Enter \"yes\" or \"no\"." << std::endl;
		std::cout << "Input is case-sensitive." << std::endl;
		std::string input;
		getline(std::cin, input, '\n');
		if (input == "yes")
		{
			newForecast();
		}
		else if (input == "no")
		{
			running = false;
			std::cout << std::endl;
			std::cout << "Have a nice day." << std::endl;
			Sleep(1750);
		}
		else
		{
			std::cout << "Invalid input. Please try again." << std::endl;
		}
	}
}