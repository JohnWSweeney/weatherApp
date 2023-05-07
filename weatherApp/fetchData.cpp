#include "weatherApp.h"
#include <filesystem>
#include <Windows.h>
#pragma comment(lib, "urlmon.lib") //

int getCoordinates(forecastData &newForecast, std::vector<std::string> &tokens)
{
	std::cout << "Enter street number, street name, and zip code:" << std::endl;
	getInput(tokens);
	// Assign first,last tokens to street number, zip code strings, respectively.
	std::string streetNum = tokens[0];
	std::string zip = tokens[tokens.size() - 1];

	// Build street name string from middle tokens.
	std::string streetName;
	for (int i = 1; i < tokens.size() - 1; i++)
	{
		streetName = streetName + "+" + tokens[i];
	}

	// Build url to US Census Bureau Geocoder.
	std::string urlStart = "https://geocoding.geo.census.gov/geocoder/locations/address?street=";
	std::string urlMiddle = streetNum + streetName + "&zip=" + zip;
	std::string urlEnd = "&benchmark=2020&format=json";
	std::string geocoderURL = urlStart + urlMiddle + urlEnd;

	// Download coordinates json file from US Census Bureau Geocoder.
	int result = downloadFileFromURL(geocoderURL, newForecast.coordinatesFilepath);
	if (result == 1)
	{
		std::cout << "Coordinates downloaded." << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Coordinates download failed." << std::endl;
		return 0;
	}
}

int verifyCoordinates(forecastData &newForecast)
{
	// Verify coordinates field is populated in json file, copy coordinates.
	std::ifstream coordinatesJSON(newForecast.coordinatesFilepath);
	std::stringstream coordinatesJSONBuffer;
	coordinatesJSONBuffer << coordinatesJSON.rdbuf();
	json coordinatesData = nlohmann::json::parse(coordinatesJSONBuffer.str());
	if (coordinatesData["result"]["addressMatches"].empty())
	{
		std::cout << "Invalid address." << std::endl;
		return 0;
	}
	else
	{
		std::cout << "Valid coordinates found." << std::endl;
		newForecast.lat = coordinatesData["result"]["addressMatches"][0]["coordinates"]["y"].get<float>();
		newForecast.lon = coordinatesData["result"]["addressMatches"][0]["coordinates"]["x"].get<float>();
		return 1;
	}
}

int getStation(forecastData &newForecast)
{
	std::cout << "lat: " << newForecast.lat << '\t' << "long: " << newForecast.lon << std::endl;

	// Build url to National Weather Service.
	std::string url = "https://api.weather.gov/points/";
	std::string latSTr = std::to_string(newForecast.lat);
	std::string lonStr = std::to_string(newForecast.lon);
	url = url + latSTr + "," + lonStr;

	int result = downloadFileFromURL(url, newForecast.stationFilepath);
	if (result == 1)
	{
		std::cout << "Station data downloaded." << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Station data download failed." << std::endl;
		return 0;
	}

}

int downloadForecasts(forecastData &newForecast)
{
	// Extract forecast, forecastHourly json links from station json.
	std::ifstream stationJSON(newForecast.stationFilepath);
	std::stringstream stationJSONBuffer;
	stationJSONBuffer << stationJSON.rdbuf();
	json stationData = nlohmann::json::parse(stationJSONBuffer.str());
	std::string forecastURL = stationData["properties"]["forecast"].get<std::string>();
	std::string hourlyForecastURL = stationData["properties"]["forecastHourly"].get<std::string>();

	// Download forecast, hourly forcast json files from National Weather Service.
	int result = downloadFileFromURL(forecastURL, newForecast.forecastFilepath);
	if (result == 1)
	{
		std::cout << "Forecast downloaded." << std::endl;
	}
	else
	{
		std::cout << "Forecast download failed." << std::endl;
		return 0;
	}

	result = downloadFileFromURL(hourlyForecastURL, newForecast.hourlyForecastFilepath);
	if (result == 1)
	{
		std::cout << "Hourly forecast downloaded." << std::endl;
		return 1;
	}
	else {
		std::cout << "Hourly forecast download failed." << '\n' << std::endl;
		return 0;
	}
}