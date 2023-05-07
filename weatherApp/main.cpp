#include "weatherApp.h"

int main()
{
	std::cout << "weatherApp v1.2.0" << std::endl;
	bool running = true;
	std::vector<std::string> tokens;
	forecastData newForecast;
	getFilepaths(newForecast);
	while (running)
	{
		int result = getForecast(newForecast, tokens);
		if (result == 0)
		{
			newForecast.clearData();
			cleanup(newForecast);
		}
		queryNewForecast(running, tokens);
	}
	cleanup(newForecast);
}