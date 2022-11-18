#include "Watchy_7_SEG.h"

#define DARKMODE true

const uint8_t BATTERY_SEGMENT_WIDTH = 7;
const uint8_t BATTERY_SEGMENT_HEIGHT = 11;
const uint8_t BATTERY_SEGMENT_SPACING = 9;
const uint8_t WEATHER_ICON_WIDTH = 48;
const uint8_t WEATHER_ICON_HEIGHT = 32;
const uint8_t SCREEN_WIDTH = 200;
const uint8_t SCREEN_HEIGHT = 200;

void Watchy7SEG::drawWatchFace()
{
    int top = 170;
    int left = 140;
    display.fillScreen(DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
    display.setTextColor(DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    drawTime();
    drawDate();
    drawSteps();
    drawWeather();
    drawBattery();
    display.drawBitmap(left - 10, top + 6, WIFI_CONFIGURED ? wifi : wifioff, 26, 18, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    if (BLE_CONFIGURED)
    {
        display.drawBitmap(left - 30, top + 3, bluetooth, 13, 21, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }
}

void Watchy7SEG::drawTime()
{
    display.setFont(&Got725Bd39pt7b);
    int displayHours;
    displayHours = ((currentTime.Hour + 11) % 12) + 1;
    display.setCursor(1, 53 + 5);
    display.print(displayHours);
    display.print(":");
    if (currentTime.Minute < 10)
    {
        display.print("0");
    }
    display.println(currentTime.Minute);
}

void Watchy7SEG::drawDate()
{
    String dayOfWeek = dayStr(currentTime.Wday);
    String month = monthShortStr(currentTime.Month);
    int16_t x1, y1;
    uint16_t w, h;
    display.fillRect(1, 68, 200, 2, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    display.setFont(&Got725Bd9pt7b);
    String fullDate = dayOfWeek + ", " + month + " " + String(currentTime.Day) + " " + String(tmYearToCalendar(currentTime.Year));
    display.getTextBounds(fullDate, 1, 85, &x1, &y1, &w, &h);
    display.setCursor(1 - (w / 2) + (SCREEN_WIDTH / 2), 85);
    display.println(fullDate);
}

void Watchy7SEG::drawSteps()
{
    int left = 1;
    int top = 175;
    // reset step counter at midnight
    if (currentTime.Hour == 0 && currentTime.Minute == 0)
    {
        sensor.resetStepCounter();
    }
    uint32_t stepCount = sensor.getCounter();
    display.drawBitmap(left + 1, top, steps, 19, 23, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    display.setCursor(left + 24, top + 17);
    display.setFont(&Got725Bd9pt7b);
    display.println(stepCount);
}
void Watchy7SEG::drawBattery()
{
    int left = 160;
    int top = 175;
    display.drawBitmap(left, top, battery, 37, 21, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    display.fillRect(left + 5, top + 5, 27, BATTERY_SEGMENT_HEIGHT, DARKMODE ? GxEPD_BLACK : GxEPD_WHITE); // clear battery segments
    int8_t batteryLevel = 0;
    float VBAT = getBatteryVoltage();
    if (VBAT > 4.1)
    {
        batteryLevel = 3;
    }
    else if (VBAT > 3.95 && VBAT <= 4.1)
    {
        batteryLevel = 2;
    }
    else if (VBAT > 3.80 && VBAT <= 3.95)
    {
        batteryLevel = 1;
    }
    else if (VBAT <= 3.80)
    {
        batteryLevel = 0;
    }

    for (int8_t batterySegments = 0; batterySegments < batteryLevel; batterySegments++)
    {
        display.fillRect(left + 5 + (batterySegments * BATTERY_SEGMENT_SPACING), top + 5, BATTERY_SEGMENT_WIDTH, BATTERY_SEGMENT_HEIGHT, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }
}

void Watchy7SEG::drawWeather()
{
    int top = 120;

    weatherData currentWeather = getWeatherData();

    int8_t temperature = currentWeather.temperature;
    int16_t weatherConditionCode = currentWeather.weatherConditionCode;

    display.setFont(&Got725Bd15pt7b);
    int16_t x1, y1;
    uint16_t w, h;
    String tempType = currentWeather.isMetric ? "c" : "f";
    String fullTemp = String(temperature) + "°" + tempType;
    display.getTextBounds(fullTemp, 0, 0, &x1, &y1, &w, &h);
    display.setCursor(1, top);
    display.println(fullTemp);
    const unsigned char *weatherIcon;

    // https://openweathermap.org/weather-conditions
    if (weatherConditionCode > 801)
    { // Cloudy
        weatherIcon = cloudy;
    }
    else if (weatherConditionCode == 801)
    { // Few Clouds
        weatherIcon = cloudsun;
    }
    else if (weatherConditionCode == 800)
    { // Clear
        weatherIcon = sunny;
    }
    else if (weatherConditionCode >= 700)
    { // Atmosphere
        weatherIcon = atmosphere;
    }
    else if (weatherConditionCode >= 600)
    { // Snow
        weatherIcon = snow;
    }
    else if (weatherConditionCode >= 500)
    { // Rain
        weatherIcon = rain;
    }
    else if (weatherConditionCode >= 300)
    { // Drizzle
        weatherIcon = drizzle;
    }
    else if (weatherConditionCode >= 200)
    { // Thunderstorm
        weatherIcon = thunderstorm;
    }
    else
        return;
    display.drawBitmap(200 - 48, 95, weatherIcon, WEATHER_ICON_WIDTH, WEATHER_ICON_HEIGHT, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
}
