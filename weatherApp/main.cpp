#include <iostream>
#include <Windows.h>
#include <string>
#pragma comment(lib, "urlmon.lib")
////
#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void getForecast()
{
	// Get station data
	std::string filePath = "D:/CPP/weatherApp/weatherApp/stationData.json";
	std::string url = "https://api.weather.gov/points/30.1799,-92.0557";

	LPCTSTR wsFilePath = filePath.c_str();
	LPCTSTR wsUrl = url.c_str();

	if (S_OK == URLDownloadToFile(NULL, wsUrl, wsFilePath, 0, NULL)) {
		std::cout << "Station data downloaded." << std::endl;
	}
	else {
		std::cout << "Station data download failed." << std::endl;
	}

	std::ifstream data("D:/CPP/weatherApp/weatherApp/stationData.json");
	std::stringstream buffer;
	buffer << data.rdbuf();
	json stationData = nlohmann::json::parse(buffer.str());
	
	// Get forecast
	std::string forecastFilePath = "D:/CPP/weatherApp/weatherApp/forecast.json";
	std::string forecastURL = stationData["properties"]["forecast"].get<std::string>();
	//std::cout << forecastURL << std::endl;

	LPCTSTR wsForecastFilePath = forecastFilePath.c_str();
	LPCTSTR wsForecastURL = forecastURL.c_str();

	if (S_OK == URLDownloadToFile(NULL, wsForecastURL, wsForecastFilePath, 0, NULL)) {
		std::cout << "Forecast downloaded." << std::endl;
	}
	else {
		std::cout << "Forecast download failed." << std::endl;
	}

	// Get hourly forecast
	std::string hourlyForecastFilePath = "D:/CPP/weatherApp/weatherApp/hourlyForecast.json";
	std::string hourlyForecastURL = stationData["properties"]["forecastHourly"].get<std::string>();
	//std::cout << hourlyForecastURL << std::endl;

	LPCTSTR wshourlyForecastFilePath = hourlyForecastFilePath.c_str();
	LPCTSTR wshourlyForecasttURL = hourlyForecastURL.c_str();

	if (S_OK == URLDownloadToFile(NULL, wshourlyForecasttURL, wshourlyForecastFilePath, 0, NULL)) {
		std::cout << "Hourly forecast downloaded." << std::endl;
	}
	else {
		std::cout << "Hourly forecast download failed." << '\n' << std::endl;
	}
	std::cout << std::endl;
}

int main()
{
	getForecast();

	std::ifstream data("D:/CPP/weatherApp/weatherApp/forecast.json");
	std::stringstream buffer;
	buffer << data.rdbuf();
	json forecastData = nlohmann::json::parse(buffer.str());

	std::string lastUpdate = forecastData["properties"]["updated"].get<std::string>();
	//std::cout << lastUpdate << std::endl;
	std::cout << "Current conditions:" << std::endl;
	int temp = forecastData["properties"]["periods"][0]["temperature"].get<int>();
	std::cout << "Temperature: " << temp << " \370F" << std::endl;
	std::string detailedForecast = forecastData["properties"]["periods"][0]["detailedForecast"].get<std::string>();
	std::cout << detailedForecast << std::endl;
	std::cout << std::endl;

	system("pause");
}