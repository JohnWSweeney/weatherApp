#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct forecastData
{
	std::vector<std::string> year;
	std::vector<std::string> month;
	std::vector<std::string> day;
	std::vector<std::string> dayNum;
	std::vector<std::string> hour;
	std::vector<std::string> ampm;
	std::vector<int> temperature;
	std::vector<int> precipitation;
	std::vector<int> humidity;
	std::string detailedForecast;
};

// fetData.cpp
std::string getCoordinates(float* lat, float* lon);
std::string getStation(float lat, float lon, std::string currentDirectory);
void getForecasts(std::string stationFilepath, std::string currentDirectory);

// extractData.cpp
forecastData forecastExtractor(std::string currentDirectory, forecastData);
forecastData hourlyForecastExtractor(std::string currentDirectory, forecastData);

// processData.cpp

// displayData.cpp
void currentConditions(forecastData);