#include "header.h"
#include <ctime>

void currentConditions(std::string currentDirectory)
{
	// .
	std::string forecastFilepath = currentDirectory + "/forecast.json";
	std::ifstream forecastJSON(forecastFilepath);
	std::stringstream forecastJSONBuffer;
	forecastJSONBuffer << forecastJSON.rdbuf();
	json forecastData = nlohmann::json::parse(forecastJSONBuffer.str());

	std::string lastUpdate = forecastData["properties"]["updated"].get<std::string>();
	int temp = forecastData["properties"]["periods"][0]["temperature"].get<int>();
	std::string detailedForecast = forecastData["properties"]["periods"][0]["detailedForecast"].get<std::string>();
	
	std::cout << "---------------------------------" << std::endl;
	std::cout << "Current conditions:" << std::endl;
	std::cout << "Temperature: " << temp << " \370F" << std::endl;
	std::cout << detailedForecast << std::endl;
}

void forecast(std::string currentDirectory)
{
	// .
	std::string hourlyForecastFilepath = currentDirectory + "/hourlyForecast.json";
	std::ifstream hourlyForecastJSON(hourlyForecastFilepath);
	std::stringstream hourlyForecastJSONBuffer;
	hourlyForecastJSONBuffer << hourlyForecastJSON.rdbuf();
	json hourlyForecastData = nlohmann::json::parse(hourlyForecastJSONBuffer.str());

	int year, month, day, hour;
	for (int i = 0; i < 156; i++)
	{
		std::string dateStr = hourlyForecastData["properties"]["periods"][i]["startTime"].get<std::string>();
		const char *dateStrBuffer = dateStr.c_str();
		sscanf_s(dateStrBuffer, "%d-%d-%dT%d", &year, &month, &day, &hour);
		std::tm timestamp{};
		timestamp.tm_year = year - 1900;
		timestamp.tm_mon = month - 1;
		timestamp.tm_mday = day;
		timestamp.tm_hour = hour;
		timestamp.tm_isdst = 0;
		std::mktime(&timestamp);

		char d[32];
		char prevD[32];
		char dayNum[32];
		char hr[32];
		char ampm[32];
		char mon[32];
		std::strftime(d, sizeof(d), "%A", &timestamp);
		std::strftime(dayNum, sizeof(dayNum), "%d", &timestamp);
		std::strftime(hr, sizeof(hr), "%I", &timestamp);
		std::strftime(ampm, sizeof(ampm), "%p", &timestamp);
		std::strftime(mon, sizeof(mon), "%B", &timestamp);

		int temp = hourlyForecastData["properties"]["periods"][i]["temperature"].get<int>();
		int pop = hourlyForecastData["properties"]["periods"][i]["probabilityOfPrecipitation"]["value"].get<int>();
		int relHum = hourlyForecastData["properties"]["periods"][i]["relativeHumidity"]["value"].get<int>();

		if (strcmp(d, prevD) == 0)
		{
			std::cout << hr << " " << ampm << "\t" << temp << " \370F" << "\t" << pop << "%" << "\t" << relHum << "%" << std::endl;
		}
		else
		{
			std::cout << "---------------------------------" << std::endl;
			std::cout << d << " " << mon << " " << dayNum << std::endl;
			std::cout << "\t" << "Temp:" << "\t" << "Precip:" << "\t" << "Humidity:" << std::endl;
			std::cout << hr << " " << ampm << "\t" << temp << " \370F" << "\t" << pop << "%" << "\t" << relHum << "%" << std::endl;
		}
		strcpy_s(prevD, d);
	}
}