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

struct dailyForecast
{
	std::string year;
	std::string month;
	std::string day;
	std::string dayNum;
	int temperatureMax;
	int temperatureMin;
	int precipitationMax;
	int precipitationMin;
	int humidityMax;
	int humidityMin;
	int index = 0;
};

// fetchData.cpp
std::string getCoordinates(float* lat, float* lon);
std::string getStation(float lat, float lon, std::string currentDirectory);
void getForecasts(std::string stationFilepath, std::string currentDirectory);

// extractData.cpp
forecastData forecastExtractor(std::string currentDirectory, forecastData);
forecastData hourlyForecastExtractor(std::string currentDirectory, forecastData);

// processData.cpp
dailyForecast reader(forecastData newForecast, dailyForecast day, int index);

// displayData.cpp
int currentConditions(forecastData);
void singleDayForecast(dailyForecast day);
void fiveDayForecast(forecastData newForecast, int index);