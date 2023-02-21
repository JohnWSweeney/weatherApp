#include <iostream>
#include <Windows.h>
#include <string>
#pragma comment(lib, "urlmon.lib")
////
#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int getCoordinates()
{
	// Get coordinates
	std::string input, tempStr;
	std::vector<std::string> tokens;

	std::cout << "Enter street number, name, and zip code:" << std::endl;

	getline(std::cin, input, '\n');
	std::stringstream strStream(input);

	while (getline(strStream, tempStr, ' '))
	{
		tokens.push_back(tempStr);
	}

	std::string streetNum = tokens[0];
	std::string zip = tokens[tokens.size() - 1];
	
	std::string filePath = "D:/CPP/weatherApp/weatherApp/coordinates.json";
	std::string urlStart = "https://geocoding.geo.census.gov/geocoder/locations/address?street=";
	std::string urlEnd = "&benchmark=2020&format=json";
	std::string urlMid;

	std::string dummyUrl = "https://old.reddit.com/r/asdfasdfasdfasdfasdfasdfasdfasdfasfsdfasdf/";

	for (int i = 1; i < tokens.size() - 1; i++)
	{
		urlMid = urlMid + "+" + tokens[i];
	}

	urlMid = streetNum + urlMid + "&zip=" + zip;

	std::string url = urlStart + urlMid + urlEnd;

	LPCTSTR wsFilePath = filePath.c_str();
	LPCTSTR wsUrl = url.c_str();
	LPCTSTR wsDummyUrl = dummyUrl.c_str();

	//if (S_OK == URLDownloadToFile(NULL, wsUrl, wsFilePath, 0, NULL)) {
	if (S_OK == URLDownloadToFile(NULL, wsDummyUrl, wsFilePath, 0, NULL)) {
		std::cout << "Coordinates downloaded." << std::endl;
	}
	else {
		std::cout << "Coordinates download failed." << std::endl;
		return 0;
	}

	//empty check
	std::ifstream data("D:/CPP/weatherApp/weatherApp/coordinates.json");
	std::stringstream buffer;
	buffer << data.rdbuf();
	json asdf = nlohmann::json::parse(buffer.str());

	if (asdf["result"]["addressMatches"].empty())
	{
		std::cout << "Invalid address." << std::endl;
		return 0;
	}
	else
	{
		std::cout << "Valid coordinates found." << std::endl;
		return 1;
	}
	
}

void getForecast()
{
	// Get station data
	std::string filePath = "D:/CPP/weatherApp/weatherApp/stationData.json";

	std::ifstream data("D:/CPP/weatherApp/weatherApp/coordinates.json");
	std::stringstream buffer;
	buffer << data.rdbuf();
	json asdf = nlohmann::json::parse(buffer.str());

	float x = asdf["result"]["addressMatches"][0]["coordinates"]["x"].get<float>();
	float y = asdf["result"]["addressMatches"][0]["coordinates"]["y"].get<float>();

	std::ostringstream sx;
	sx << x;
	std::string xStr = sx.str();

	std::ostringstream sy;
	sy << y;
	std::string yStr = sy.str();

	std::string urlStart = "https://api.weather.gov/points/";
	std::string url = urlStart + yStr + "," + xStr;

	LPCTSTR wsFilePath = filePath.c_str();
	LPCTSTR wsUrl = url.c_str();

	if (S_OK == URLDownloadToFile(NULL, wsUrl, wsFilePath, 0, NULL)) {
		std::cout << "Station data downloaded." << std::endl;
	}
	else {
		std::cout << "Station data download failed." << std::endl;
	}

	std::ifstream data1("D:/CPP/weatherApp/weatherApp/stationData.json");
	std::stringstream buffer1;
	buffer1 << data1.rdbuf();
	json stationData = nlohmann::json::parse(buffer1.str());
	
	// Get forecast
	std::string forecastFilePath = "D:/CPP/weatherApp/weatherApp/forecast.json";
	std::string forecastURL = stationData["properties"]["forecast"].get<std::string>();

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

void currentConditions()
{
	std::ifstream data("D:/CPP/weatherApp/weatherApp/forecast.json");
	std::stringstream buffer;
	buffer << data.rdbuf();
	json forecastData = nlohmann::json::parse(buffer.str());

	std::string lastUpdate = forecastData["properties"]["updated"].get<std::string>();
	std::cout << "Current conditions:" << std::endl;
	int temp = forecastData["properties"]["periods"][0]["temperature"].get<int>();
	std::cout << "Temperature: " << temp << " \370F" << std::endl;
	std::string detailedForecast = forecastData["properties"]["periods"][0]["detailedForecast"].get<std::string>();
	std::cout << detailedForecast << std::endl;
	std::cout << std::endl;
}

void hourlyForecast()
{
	std::ifstream data("D:/CPP/weatherApp/weatherApp/hourlyForecast.json");
	std::stringstream buffer;
	buffer << data.rdbuf();
	json hourlyForecastData = nlohmann::json::parse(buffer.str());

	std::cout << "Forecast:" << std::endl;
	for (int i = 0; i < 155; i++)
	{
		int temp = hourlyForecastData["properties"]["periods"][i]["temperature"].get<int>();
		std::string time = hourlyForecastData["properties"]["periods"][i]["startTime"].get<std::string>();
		std::cout << time << " " << temp << " \370F" << std::endl;
	}
}

int main()
{
	std::cout << "weatherApp v1.0.0" << std::endl;
	while (true)
	{
		int result = getCoordinates();
		if (result != 0)
		{
			getForecast();
			currentConditions();
			//hourlyForecast();
		}
	}

	//system("pause");
}