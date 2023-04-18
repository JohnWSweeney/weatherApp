#include "header.h"

forecastData forecastExtractor(std::string currentDirectory, forecastData newForecast)
{
	// .
	std::string forecastFilepath = currentDirectory + "/forecast.json";
	std::ifstream forecastJSON(forecastFilepath);
	std::stringstream forecastJSONbuf;
	forecastJSONbuf << forecastJSON.rdbuf();
	json forecast = nlohmann::json::parse(forecastJSONbuf.str());
	newForecast.detailedForecast = forecast["properties"]["periods"][0]["detailedForecast"].get<std::string>();
	return newForecast;
}

forecastData hourlyForecastExtractor(std::string currentDirectory, forecastData newForecast)
{
	// .
	std::string hourlyForecastFilepath = currentDirectory + "/hourlyForecast.json";
	std::ifstream hourlyForecastJSON(hourlyForecastFilepath);
	std::stringstream hourlyForecastJSONbuf;
	hourlyForecastJSONbuf << hourlyForecastJSON.rdbuf();
	json hourlyForecast = nlohmann::json::parse(hourlyForecastJSONbuf.str());

	int yr, mon, d, hr;
	int i = 0;
	char day[32];
	char dayNum[32];
	char hour[32];
	char ampm[32];
	char month[32];
	char year[32];

	for (int i = 0; i < 156; i++)
	{
		std::string dateStr = hourlyForecast["properties"]["periods"][i]["startTime"].get<std::string>();
		const char *dateCStr = dateStr.c_str();
		sscanf_s(dateCStr, "%d-%d-%dT%d", &yr, &mon, &d, &hr);
		std::tm timestamp{};
		timestamp.tm_year = yr - 1900;
		timestamp.tm_mon = mon - 1;
		timestamp.tm_mday = d;
		timestamp.tm_hour = hr;
		timestamp.tm_isdst = 0;
		std::mktime(&timestamp);

		std::strftime(year, sizeof(year), "%Y", &timestamp);
		std::strftime(month, sizeof(month), "%B", &timestamp);
		std::strftime(day, sizeof(day), "%A", &timestamp);
		std::strftime(dayNum, sizeof(dayNum), "%d", &timestamp);
		std::strftime(hour, sizeof(hour), "%I", &timestamp);
		std::strftime(ampm, sizeof(ampm), "%p", &timestamp);

		int temp = hourlyForecast["properties"]["periods"][i]["temperature"].get<int>();
		int pop = hourlyForecast["properties"]["periods"][i]["probabilityOfPrecipitation"]["value"].get<int>();
		int relHum = hourlyForecast["properties"]["periods"][i]["relativeHumidity"]["value"].get<int>();

		newForecast.year.push_back(year);
		newForecast.month.push_back(month);
		newForecast.day.push_back(day);
		newForecast.dayNum.push_back(dayNum);
		newForecast.hour.push_back(hour);
		newForecast.ampm.push_back(ampm);
		newForecast.temperature.push_back(temp);
		newForecast.precipitation.push_back(pop);
		newForecast.humidity.push_back(relHum);
	}
	return newForecast;
}