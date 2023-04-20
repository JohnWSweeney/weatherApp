#include "header.h"
#include <algorithm>

dailyForecast reader(forecastData newForecast, dailyForecast day, int index)
{
	// store date at first index.
	std::string ref = newForecast.day[index];
	day.year = newForecast.year[index];
	day.month = newForecast.month[index];
	day.day = newForecast.day[index];
	day.dayNum = newForecast.dayNum[index];
	// declare buffer vectors for weather fields.
	std::vector<int> tempBuf;
	std::vector<int> precipBuf;
	std::vector<int> humBuf;

	// populate buffer vectors until day changes.
	do {
		tempBuf.push_back(newForecast.temperature[index]);
		precipBuf.push_back(newForecast.precipitation[index]);
		humBuf.push_back(newForecast.humidity[index]);
		++index;
	} while (newForecast.day[index] == ref);

	// find max, min values in temp vectors.
	auto result = std::minmax_element(tempBuf.begin(), tempBuf.end());
	day.temperatureMin = *result.first;
	day.temperatureMax = *result.second;
	result = std::minmax_element(precipBuf.begin(), precipBuf.end());
	day.precipitationMin = *result.first;
	day.precipitationMax = *result.second;
	result = std::minmax_element(humBuf.begin(), humBuf.end());
	day.humidityMin = *result.first;
	day.humidityMax = *result.second;
	day.index = index;
	return day;
}