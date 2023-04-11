#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::string getCoordinates(float* lat, float* lon);
std::string getStation(float lat, float lon, std::string currentDirectory);
void getForecast(std::string stationFilepath, std::string currentDirectory);
void currentConditions(std::string currentDirectory);
void forecast(std::string currentDirectory);