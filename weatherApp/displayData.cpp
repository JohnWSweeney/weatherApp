#include "header.h"

void currentConditions(forecastData newForecast)
{
	std::cout << "---------------------------------" << std::endl;
	std::cout << newForecast.day[0] << ", " << newForecast.month[0] << " " << newForecast.dayNum[0] << ", ";
	std::cout << newForecast.year[0] << std::endl;
	std::cout << "---------------------------------" << std::endl;
	std::cout << "Current conditions:" << std::endl;
	std::cout << newForecast.temperature[0] << "\370F, ";
	std::cout << newForecast.precipitation[0] << "% chance of precipitation" << std::endl;
	std::cout << newForecast.detailedForecast << std::endl;
}

void fiveDayForecast(forecastData newForecast)
{
	dailyForecast today, tomorrow, secondDay, thirdDay, fourthDay, fifthDay;

	// today
	today = reader(newForecast, today, today.index);
	std::cout << "---------------------------------" << std::endl;
	std::cout << "Forecast for the rest of today: " << std::endl;
	std::cout << "---------------------------------" << std::endl;
	std::cout << "Temperature Max/Min: " << today.temperatureMax << ", " << today.temperatureMin << std::endl;
	std::cout << "Precipitation Max/Min: " << today.precipitationMax << ", " << today.precipitationMin << std::endl;
	std::cout << "Humidity Max/Min: " << today.humidityMax << ", " << today.humidityMin << std::endl;
	std::cout << "---------------------------------" << std::endl;
	// tomorrow
	tomorrow = reader(newForecast, tomorrow, today.index);
	std::cout << tomorrow.day << ", " << tomorrow.month << " " << tomorrow.dayNum << ", ";
	std::cout << tomorrow.year << std::endl;
	std::cout << "---------------------------------" << std::endl;
	std::cout << "Temperature Max/Min: " << tomorrow.temperatureMax << ", " << tomorrow.temperatureMin << std::endl;
	std::cout << "Precipitation Max/Min: " << tomorrow.precipitationMax << ", " << tomorrow.precipitationMin << std::endl;
	std::cout << "Humidity Max/Min: " << tomorrow.humidityMax << ", " << tomorrow.humidityMin << std::endl;
	std::cout << "---------------------------------" << std::endl;
	// second day
	secondDay = reader(newForecast, secondDay, tomorrow.index);
	std::cout << secondDay.day << ", " << secondDay.month << " " << secondDay.dayNum << ", ";
	std::cout << secondDay.year << std::endl;
	std::cout << "---------------------------------" << std::endl;
	std::cout << "Temperature Max/Min: " << secondDay.temperatureMax << ", " << secondDay.temperatureMin << std::endl;
	std::cout << "Precipitation Max/Min: " << secondDay.precipitationMax << ", " << secondDay.precipitationMin << std::endl;
	std::cout << "Humidity Max/Min: " << secondDay.humidityMax << ", " << secondDay.humidityMin << std::endl;
	std::cout << "---------------------------------" << std::endl;
	// third day
	thirdDay = reader(newForecast, thirdDay, secondDay.index);
	std::cout << thirdDay.day << ", " << thirdDay.month << " " << thirdDay.dayNum << ", ";
	std::cout << thirdDay.year << std::endl;
	std::cout << "---------------------------------" << std::endl;
	std::cout << "Temperature Max/Min: " << thirdDay.temperatureMax << ", " << thirdDay.temperatureMin << std::endl;
	std::cout << "Precipitation Max/Min: " << thirdDay.precipitationMax << ", " << thirdDay.precipitationMin << std::endl;
	std::cout << "Humidity Max/Min: " << thirdDay.humidityMax << ", " << thirdDay.humidityMin << std::endl;
	std::cout << "---------------------------------" << std::endl;
	// fourth day
	fourthDay = reader(newForecast, fourthDay, thirdDay.index);
	std::cout << fourthDay.day << ", " << fourthDay.month << " " << fourthDay.dayNum << ", ";
	std::cout << fourthDay.year << std::endl;
	std::cout << "---------------------------------" << std::endl;
	std::cout << "Temperature Max/Min: " << fourthDay.temperatureMax << ", " << fourthDay.temperatureMin << std::endl;
	std::cout << "Precipitation Max/Min: " << fourthDay.precipitationMax << ", " << fourthDay.precipitationMin << std::endl;
	std::cout << "Humidity Max/Min: " << fourthDay.humidityMax << ", " << fourthDay.humidityMin << std::endl;
	std::cout << "---------------------------------" << std::endl;
	// fifth day
	fifthDay = reader(newForecast, fifthDay, fourthDay.index);
	std::cout << fifthDay.day << ", " << fifthDay.month << " " << fifthDay.dayNum << ", ";
	std::cout << fifthDay.year << std::endl;
	std::cout << "---------------------------------" << std::endl;
	std::cout << "Temperature Max/Min: " << fifthDay.temperatureMax << ", " << fifthDay.temperatureMin << std::endl;
	std::cout << "Precipitation Max/Min: " << fifthDay.precipitationMax << ", " << fifthDay.precipitationMin << std::endl;
	std::cout << "Humidity Max/Min: " << fifthDay.humidityMax << ", " << fifthDay.humidityMin << std::endl;
	std::cout << "---------------------------------" << std::endl;
}