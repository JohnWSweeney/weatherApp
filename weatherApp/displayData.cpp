#include "weatherApp.h"

int currentConditions(forecastData newForecast)
{
	// Display today's date and forecast.
	std::cout << "---------------------------------" << std::endl;
	std::cout << newForecast.day[0] << ", " << newForecast.month[0] << " " << newForecast.dayNum[0] << ", ";
	std::cout << newForecast.year[0] << std::endl;
	std::cout << "---------------------------------" << std::endl;
	std::cout << "Current conditions:" << std::endl;
	std::cout << newForecast.temperature[0] << "\370F, ";
	std::cout << newForecast.precipitation[0] << "% chance of precipitation" << std::endl;
	std::cout << newForecast.detailedForecast << std::endl;
	// Display forecast for the rest of today.
	dailyForecast today;
	today = reader(newForecast, today, today.index);
	std::cout << "---------------------------------" << std::endl;
	std::cout << "Forecast for the rest of today:" << std::endl;
	std::cout << "---------------------------------" << std::endl;
	std::cout << "Temperature range (F): " << today.temperatureMin << "\370 - " << today.temperatureMax << "\370" << std::endl;
	std::cout << "Precipitation range (%): " << today.precipitationMin << " - " << today.precipitationMax << std::endl;
	std::cout << "Humidity range (%): " << today.humidityMin << " - " << today.humidityMax << std::endl;
	std::cout << "---------------------------------" << std::endl;
	return today.index;
}

void singleDayForecast(dailyForecast day)
{
	// Display day's date and forecast.
	std::cout << day.day << ", " << day.month << " " << day.dayNum << ", ";
	std::cout << day.year << std::endl;
	std::cout << "---------------------------------" << std::endl;
	std::cout << "Temperature range (F): " << day.temperatureMin << "\370 - " << day.temperatureMax << "\370" << std::endl;
	std::cout << "Precipitation range (%): " << day.precipitationMin << " - " << day.precipitationMax << std::endl;
	std::cout << "Humidity range (%): " << day.humidityMin << " - " << day.humidityMax << std::endl;
	std::cout << "---------------------------------" << std::endl;
}

void fiveDayForecast(forecastData newForecast, int index)
{
	dailyForecast tomorrow, secondDay, thirdDay, fourthDay, fifthDay;
	// Tomorrow's forecast.
	tomorrow = reader(newForecast, tomorrow, index);
	singleDayForecast(tomorrow);
	// Day after tommorrow's forecast.
	secondDay = reader(newForecast, secondDay, tomorrow.index);
	singleDayForecast(secondDay);
	// Third day's forecast.
	thirdDay = reader(newForecast, thirdDay, secondDay.index);
	singleDayForecast(thirdDay);
	// Fourth day's forecast.
	fourthDay = reader(newForecast, fourthDay, thirdDay.index);
	singleDayForecast(fourthDay);
	// Fifth day's forecast.
	fifthDay = reader(newForecast, fifthDay, fourthDay.index);
	singleDayForecast(fifthDay);
}