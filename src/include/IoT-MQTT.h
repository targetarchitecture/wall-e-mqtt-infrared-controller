#pragma once

#include <PubSubClient.h>
#include <sstream>

void MessageReceived(char *topic, byte *payload, unsigned int length);
void loopMQTTClient();
void setupMQTTClient();

extern void sendWallECommand(std::string topic, std::string message);