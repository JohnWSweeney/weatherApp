#include "header.h"
#include <filesystem>
#include <Windows.h>
#pragma comment(lib, "urlmon.lib") //

std::string getCoordinates(float* lat, float* lon)
{
	std::cout << "Enter street number, street name, and zip code:" << std::endl;

	std::string input, tempStr;
	std::vector<std::string> tokens;

	// Tokenize user input.
	std::getline(std::cin, input, '\n');
	std::stringstream strStream(input);
	while (getline(strStream, tempStr, ' '))
	{
		tokens.push_back(tempStr);
	}

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
	LPCTSTR lpctstrGeocoderURL = geocoderURL.c_str(); // null-terminated.

	// Build file path for coordinates json file.
	std::filesystem::path currentDirectoryPath = std::filesystem::current_path();
	std::string currentDirectory = currentDirectoryPath.string();
	std::string coordinatesFilepath = currentDirectory + "/coordinates.json";
	LPCTSTR lpctstrFilepath = coordinatesFilepath.c_str();

	// Download coordinates json file from US Census Bureau Geocoder.
	if (S_OK == URLDownloadToFile(NULL, lpctstrGeocoderURL, lpctstrFilepath, 0, NULL))
	{
		std::cout << "Coordinates downloaded." << std::endl;
	}
	else
	{
		std::cout << "Coordinates download failed." << std::endl;
	}

	// Verify coordinates field is populated in json file, copy coordinates.
	std::ifstream coordinatesJSON(coordinatesFilepath);
	std::stringstream coordinatesJSONBuffer;
	coordinatesJSONBuffer << coordinatesJSON.rdbuf();
	json coordinatesData = nlohmann::json::parse(coordinatesJSONBuffer.str());
	if (coordinatesData["result"]["addressMatches"].empty())
	{
		std::cout << "Invalid address." << std::endl;
	}
	else
	{
		std::cout << "Valid coordinates found." << std::endl;
		*lat = coordinatesData["result"]["addressMatches"][0]["coordinates"]["y"].get<float>();
		*lon = coordinatesData["result"]["addressMatches"][0]["coordinates"]["x"].get<float>();
	}

	return currentDirectory;
}

std::string getStation(float lat, float lon, std::string currentDirectory)
{
	std::cout << "lat: " << lat << '\t' << "long: " << lon << std::endl;

	// Build url to National Weather Service.
	std::string url = "https://api.weather.gov/points/";
	std::string latSTr = std::to_string(lat);
	std::string lonStr = std::to_string(lon);
	url = url + latSTr + "," + lonStr;
	LPCTSTR lpctstrURL = url.c_str();

	// Build file path for station json file.
	std::string stationFilepath = currentDirectory + "/station.json";
	LPCTSTR lpctstrfilepath = stationFilepath.c_str();

	// Download station data from National Weather Service.
	if (S_OK == URLDownloadToFile(NULL, lpctstrURL, lpctstrfilepath, 0, NULL))
	{
		std::cout << "Station data downloaded." << std::endl;
	}
	else

	{
		std::cout << "Station data download failed." << std::endl;
	}
	return stationFilepath;
}

void getForecast(std::string stationFilepath, std::string currentDirectory)
{
	// Build file paths for forecast, hourly forecast json files.
	std::string forecastFilepath = currentDirectory + "/forecast.json";
	std::string hourlyForecastFilepath = currentDirectory + "/hourlyForecast.json";
	LPCTSTR lpctstrForecastFilepath = forecastFilepath.c_str();
	LPCTSTR lpctstrHourlyForecastFilepath = hourlyForecastFilepath.c_str();

	// Extract forecast, forecastHourly json links from station json.
	std::ifstream stationJSON(stationFilepath);
	std::stringstream stationJSONBuffer;
	stationJSONBuffer << stationJSON.rdbuf();
	json stationData = nlohmann::json::parse(stationJSONBuffer.str());
	std::string forecastURL = stationData["properties"]["forecast"].get<std::string>();
	std::string hourlyForecastURL = stationData["properties"]["forecastHourly"].get<std::string>();
	LPCTSTR lpctstrForecastURL = forecastURL.c_str();
	LPCTSTR lpctstrHourlyForecastURL = hourlyForecastURL.c_str();

	// Download forecast, hourly forcast json files from National Weather Service.
	if (S_OK == URLDownloadToFile(NULL, lpctstrForecastURL, lpctstrForecastFilepath, 0, NULL)) {
		std::cout << "Forecast downloaded." << std::endl;
	}
	else {
		std::cout << "Forecast download failed." << std::endl;
	}

	if (S_OK == URLDownloadToFile(NULL, lpctstrHourlyForecastURL, lpctstrHourlyForecastFilepath, 0, NULL)) {
		std::cout << "Hourly forecast downloaded." << std::endl;
	}
	else {
		std::cout << "Hourly forecast download failed." << '\n' << std::endl;
	}
}