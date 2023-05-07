#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <Windows.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct forecastData
{
	float lat;
	float lon;
	std::string currentDirectory;
	std::string coordinatesFilepath;
	std::string stationFilepath;
	std::string forecastFilepath;
	std::string hourlyForecastFilepath;
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
	void clearData();
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

// start.cpp
void getInput(std::vector<std::string> &tokens);
int getForecast(forecastData &newForecast, std::vector<std::string> &tokens);
void queryNewForecast(bool &running, std::vector<std::string> &tokens);

// fetchData.cpp
int getCoordinates(forecastData &newForecast, std::vector<std::string> &tokens);
int verifyCoordinates(forecastData &newForecast);
int getStation(forecastData &newForecast);
int downloadForecasts(forecastData &newForecast);

// extractData.cpp
void forecastExtractor(forecastData &newForecast);
void hourlyForecastExtractor(forecastData &newForecast);

// processData.cpp
dailyForecast reader(forecastData newForecast, dailyForecast day, int index);

// displayData.cpp
int currentConditions(forecastData);
void singleDayForecast(dailyForecast day);
void fiveDayForecast(forecastData newForecast, int index);

// housekeeping.cpp
int downloadFileFromURL(std::string url, std::string filepath);
void getFilepaths(forecastData &newForecast);
void cleanup(forecastData &newForecast);