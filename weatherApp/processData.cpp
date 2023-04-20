#include "header.h"
#include <algorithm>

dailyForecast reader(forecastData newForecast, dailyForecast day, int i)
{
	std::string ref = newForecast.day[i];
	day.year = newForecast.year[i];
	day.month = newForecast.month[i];
	day.day = newForecast.day[i];
	day.dayNum = newForecast.dayNum[i];
	std::vector<int> tempBuf;
	std::vector<int> popBuf;
	std::vector<int> humBuf;

	do {
		tempBuf.push_back(newForecast.temperature[i]);
		popBuf.push_back(newForecast.precipitation[i]);
		humBuf.push_back(newForecast.humidity[i]);
		++i;
	} while (newForecast.day[i] == ref);

	auto result = std::minmax_element(tempBuf.begin(), tempBuf.end());
	day.temperatureMin = *result.first;
	day.temperatureMax = *result.second;
	result = std::minmax_element(popBuf.begin(), popBuf.end());
	day.precipitationMin = *result.first;
	day.precipitationMax = *result.second;
	result = std::minmax_element(humBuf.begin(), humBuf.end());
	day.humidityMin = *result.first;
	day.humidityMax = *result.second;
	day.index = i;

	return day;
}