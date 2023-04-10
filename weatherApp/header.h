#pragma once
#include <iostream>

std::string getCoordinates(float* lat, float* lon);
std::string getStation(float lat, float lon, std::string currentDirectory);
void getForecast(std::string stationFilepath, std::string currentDirectory);
void currentConditions(std::string currentDirectory);