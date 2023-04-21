# weatherApp

A console app returning current conditions and a five day forecast provided by the US National Weather Service.

Enter *streetNumber streetName zipCode* to get forecast. For example, enter
> 175 5th 10010

for a forecast near the NYC Flatiron Building.

### Motivation
I wanted a project that would develop my coding skills and also do something useful. Building v1 required learning json and improved my understanding of data structures, functions, program architeture, and basic data analysis. I also wanted this project to be free to write and use, so I was limited to open-source data. Fortunately, the US National Weather Service (NWS) provides a free API with lots of interesting weather day to play with.

### Design Overview
The NWS API requires the user to provide latitude and longitude coordinates to receive a forecast. Convieniently, the US Census Bureau has a free API that returns coordinates (via json) for an address.

So the basic order of operations is as follows:
- Ask user for address.
- Get coordinates from US Census Bureau with user address.
- Download NWS station data json.
- Download forecast and hourly forecast jsons via links in NWS station data json.
- Extract and store relevant data from forecast jsons in a struct or class.
- Process data for a display of current conditions and five day forecast.

### Future Updates
- Auto location detection (IP address, GPS).
- GUI version.

### Known Issues
- App crashes on invalid address input or may report previous forecast data.
  - High priority: functions need error/exception handling.
- User input on new forecast prompt is case-sensitive.