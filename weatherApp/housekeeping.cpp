#include "weatherApp.h"

int downloadFileFromURL(std::string url, std::string filepath)
{
	LPCTSTR lpctstrURL = url.c_str();
	LPCTSTR lpctstrfilepath = filepath.c_str();

	if (S_OK == URLDownloadToFile(NULL, lpctstrURL, lpctstrfilepath, 0, NULL))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void forecastData::clearData()
{
	// Clear all previous forecast data.
	year = {};
	month = {};
	day = {};
	dayNum = {};
	hour = {};
	ampm = {};
	temperature = {};
	precipitation = {};
	humidity = {};
	detailedForecast = {};
}

void getFilepaths(forecastData &newForecast)
{
	// Identify current directory and populate json filepaths.
	std::filesystem::path currentDirectoryPath = std::filesystem::current_path();
	newForecast.currentDirectory = currentDirectoryPath.string();
	newForecast.coordinatesFilepath = newForecast.currentDirectory + "\\coordinates.json";
	newForecast.stationFilepath = newForecast.currentDirectory + "\\station.json";
	newForecast.forecastFilepath = newForecast.currentDirectory + "\\forecast.json";
	newForecast.hourlyForecastFilepath = newForecast.currentDirectory + "\\hourlyForecast.json";
}

void cleanup(forecastData &newForecast)
{
	// Delete all downloaded json files.
	LPCTSTR coordinatesFilepath = newForecast.coordinatesFilepath.c_str();
	bool deleteSucceed = DeleteFile(coordinatesFilepath);
	LPCTSTR stationFilepath = newForecast.stationFilepath.c_str();
	deleteSucceed = DeleteFile(stationFilepath);
	LPCTSTR forecastFilepath = newForecast.forecastFilepath.c_str();
	deleteSucceed = DeleteFile(forecastFilepath);
	LPCTSTR hourlyForecastFilepath = newForecast.hourlyForecastFilepath.c_str();
	deleteSucceed = DeleteFile(hourlyForecastFilepath);
}