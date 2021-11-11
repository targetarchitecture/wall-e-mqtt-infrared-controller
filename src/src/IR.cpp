#include <Arduino.h>
#include "IR.h"
#include "topics.h"
#include "pronto.h"

IRsend irsend(kIrLed); // Set the GPIO to be used to sending the message.

void setupIR()
{
    irsend.begin();
}

void sendWallECommand(std::string topic, std::string message)
{
    if (std::string(topic) == std::string(MQTT_DANCE_TOPIC))
    {
        Serial.println("Sending a WALL-E 'Dance' command.");

        irsend.sendPronto(danceCommand, 48);
    }
    else if (std::string(topic) == std::string(MQTT_MUSIC_TOPIC))
    {
        Serial.println("Sending a WALL-E 'Music' command.");

        irsend.sendPronto(musicCommand, 48);
    }
    else if (std::string(topic) == std::string(MQTT_LIGHT_TOPIC))
    {
        Serial.println("Sending a WALL-E 'Light' command.");

        irsend.sendPronto(lightCommand, 48);
    }
    else if (std::string(topic) == std::string(MQTT_EYES_TOPIC))
    {
        Serial.println("Sending a WALL-E 'Eyes' command.");

        irsend.sendPronto(eyesCommand, 48);
    }
    else if (std::string(topic) == std::string(MQTT_CIRCLE_TOPIC))
    {
        Serial.println("Sending a WALL-E 'Circle' command.");

        irsend.sendPronto(circleCommand, 48);
    }
    else if (std::string(topic) == std::string(MQTT_ROTATE_TOPIC))
    {
        Serial.println("Sending a WALL-E 'Rotate' command.");

        irsend.sendPronto(rotateCommand, 48);
    }
    else if (std::string(topic) == std::string(MQTT_TURN_TOPIC))
    {
        Serial.println("Sending a WALL-E 'Turn' command.");

        irsend.sendPronto(turnCommand, 48);
    }
    else if (std::string(topic) == std::string(MQTT_AHEAD_TOPIC))
    {
        Serial.println("Sending a WALL-E 'Ahead' command.");

        irsend.sendPronto(aheadCommand, 48);
    }
    else if (std::string(topic) == std::string(MQTT_BACKWARD_TOPIC))
    {
        Serial.println("Sending a WALL-E 'Backward' command.");

        irsend.sendPronto(backwardCommand, 48);
    }
    else if (std::string(topic) == std::string(MQTT_FORWARD_TOPIC))
    {
        Serial.println("Sending a WALL-E 'Forward' command.");

        irsend.sendPronto(forwardCommand, 48);
    }
}
