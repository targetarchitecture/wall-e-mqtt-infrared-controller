#pragma once

#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <sstream>

const uint16_t kIrLed = 4; // ESP8266 GPIO pin to use. Recommended: 4 (D2).

void sendWallECommand(std::string topic, std::string message);
void setupIR();