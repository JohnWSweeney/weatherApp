#include "header.h"
#include <sstream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void currentConditions(std::string currentDirectory)
{
	// .
	std::string forecastFilepath = currentDirectory + "/forecast.json";
	std::ifstream forecastJSON(forecastFilepath);
	std::stringstream forecastJSONBuffer;
	forecastJSONBuffer << forecastJSON.rdbuf();
	json forecastData = nlohmann::json::parse(forecastJSONBuffer.str());

	std::string lastUpdate = forecastData["properties"]["updated"].get<std::string>();
	int temp = forecastData["properties"]["periods"][0]["temperature"].get<int>();
	std::string detailedForecast = forecastData["properties"]["periods"][0]["detailedForecast"].get<std::string>();
	
	std::cout << "-------------------" << std::endl;
	std::cout << "Current conditions:" << std::endl;
	std::cout << "Temperature: " << temp << " \370F" << std::endl;
	std::cout << detailedForecast << std::endl;
	std::cout << "-------------------" << std::endl;
	std::cout << std::endl;
}