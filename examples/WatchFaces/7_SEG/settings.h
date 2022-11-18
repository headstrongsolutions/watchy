#ifndef SETTINGS_H
#define SETTINGS_H

// Weather Settings
#define CITY_ID "2657355"                                                       // New York City https://openweathermap.org/current#cityid
#define OPENWEATHERMAP_APIKEY "87b3019f8185962b9c7d5e1ea2a40be7"                // use your own API key :)
#define OPENWEATHERMAP_URL "http://api.openweathermap.org/data/2.5/weather?id=" // open weather api
#define TEMP_UNIT "metric"                                                      // metric = Celsius , imperial = Fahrenheit
#define TEMP_LANG "en"
#define WEATHER_UPDATE_INTERVAL 30 // must be greater than 5, measured in minutes
// NTP Settings
#define NTP_SERVER "pool.ntp.org"
#define GMT_OFFSET_SEC 3600 * +1 // New York is UTC -5
#define DST_OFFSET_SEC 3600

watchySettings settings{
    CITY_ID,
    OPENWEATHERMAP_APIKEY,
    OPENWEATHERMAP_URL,
    TEMP_UNIT,
    TEMP_LANG,
    WEATHER_UPDATE_INTERVAL,
    NTP_SERVER,
    GMT_OFFSET_SEC,
    DST_OFFSET_SEC};

#endif