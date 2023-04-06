#include "header.h"
#include <sstream>
#include <fstream>
#include <filesystem>
#include <Windows.h>
#pragma comment(lib, "urlmon.lib") //
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void getCoordinates()
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
	std::filesystem::path currentDirectory = std::filesystem::current_path();
	std::string filepath = currentDirectory.string() + "/coordinates.json";
	LPCTSTR lpctstrFilepath = filepath.c_str();

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
	std::ifstream asdf(filepath);
	std::stringstream fdsa;
	fdsa << asdf.rdbuf();
	json coordinates = nlohmann::json::parse(fdsa.str());
	if (coordinates["result"]["addressMatches"].empty())
	{
		std::cout << "Invalid address." << std::endl;
	}
	else
	{
		std::cout << "Valid coordinates found." << std::endl;
		float lat = coordinates["result"]["addressMatches"][0]["coordinates"]["x"].get<float>();
		float lon = coordinates["result"]["addressMatches"][0]["coordinates"]["y"].get<float>();
		std::cout << "lat: " << lat << '\t' << "long: " << lon << std::endl;
	}
}