#include "weatherApp.h"

void getInput(std::vector<std::string> &tokens)
{
	// Copy each word in user input to vector (tokenize).
	tokens.clear();
	do {
		std::string input, tempStr;
		std::getline(std::cin, input, '\n');
		std::stringstream strStream(input);
		while (getline(strStream, tempStr, ' '))
		{
			tokens.push_back(tempStr);
		}
	} while (tokens.empty());
}

void selectOption(std::vector<std::string> &tokens, bool &running)
{
	// Repeat until user enters valid iput command.
	bool repeat = true;
	do {
		if (tokens[0] == "yes")
		{
			repeat = false;
		}
		else if (tokens[0] == "no")
		{
			running = false;
			repeat = false;
			std::cout << std::endl;
			std::cout << "Have a nice day." << std::endl;
			Sleep(1750);
		}
		else
		{
			std::cout << "Invalid input. Please try again." << std::endl;
		}
	} while (repeat);
}

int getForecast(forecastData &newForecast, std::vector<std::string> &tokens)
{
	std::cout << std::endl;

	// Fetch data.
	int result = getCoordinates(newForecast, tokens);
	if (result == 0)
	{
		std::cout << "getCoordinates failed." << std::endl;
		return 0;
	}

	// Get geocoordinates json.
	result = verifyCoordinates(newForecast);
	if (result == 0)
	{
		std::cout << "verifyCoordinates failed." << std::endl;
		return 0;
	}
	
	// Get station json.
	result = getStation(newForecast);
	if (result == 0)
	{
		std::cout << "getStation failed." << std::endl;
		return 0;
	}

	// Download forecast and hourly forecast jsons.
	result = downloadForecasts(newForecast);
	if (result == 0)
	{
		std::cout << "downloadForecasts failed." << std::endl;
		return 0;
	}

	// Extract data.
	forecastExtractor(newForecast);
	hourlyForecastExtractor(newForecast);

	// Display forecasts.
	int index = currentConditions(newForecast);
	fiveDayForecast(newForecast, index);
}

void queryNewForecast(bool &running, std::vector<std::string> &tokens)
{
	std::cout << std::endl;
	std::cout << "Would you like a new forecast? Enter \"yes\" or \"no\"." << std::endl;
	std::cout << "Input is case-sensitive." << std::endl;
	getInput(tokens);
	selectOption(tokens, running);
}