#pragma once

#include <ESP8266WiFi.h>

void setupWifi();
void onWifiConnect(const WiFiEventStationModeGotIP &event);
void onWifiDisconnect(const WiFiEventStationModeDisconnected &event);


