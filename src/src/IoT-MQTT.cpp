#include <Arduino.h>
#include "IoT-MQTT.h"
#include <ESP8266WiFi.h>
#include "credentials.h"
#include "topics.h"

WiFiClient wifiConnection;
PubSubClient MQTTClient(wifiConnection);

unsigned long previousSendIPMillis = millis();

void setupMQTTClient()
{
    Serial.println("Setting up MQTT server parameters");

    //set this to be a large enough value to allow a large MQTT message
    //MQTTClient.setBufferSize(5000);

    MQTTClient.setServer(MQTT_SERVER, 1883);

    // setup callbacks
    MQTTClient.setCallback(MessageReceived);
}

void MQTTConnect()
{
    yield();

    Serial.print("Attempting MQTT connection...");

    auto connectionTiming = millis();

    // Attempt to connect
    if (MQTTClient.connect(MQTT_CLIENTID, MQTT_USERNAME, MQTT_KEY))
    {
        //set LED on
        digitalWrite(LED_BUILTIN, LOW);

        Serial.println("MQTT connected");
        Serial.print("connected in ");
        Serial.print(millis() - connectionTiming);
        Serial.println("ms");

        // Once connected, publish an announcement...
        MQTTClient.publish(MQTT_INFO_TOPIC, "Connected");

        //and resubscribe
        MQTTClient.subscribe(MQTT_FORWARD_TOPIC);
        MQTTClient.subscribe(MQTT_BACKWARD_TOPIC);
        MQTTClient.subscribe(MQTT_AHEAD_TOPIC);
        MQTTClient.subscribe(MQTT_TURN_TOPIC);
        MQTTClient.subscribe(MQTT_ROTATE_TOPIC);
        MQTTClient.subscribe(MQTT_CIRCLE_TOPIC);
        MQTTClient.subscribe(MQTT_LIGHT_TOPIC);
        MQTTClient.subscribe(MQTT_MUSIC_TOPIC);
        MQTTClient.subscribe(MQTT_DANCE_TOPIC);
        MQTTClient.subscribe(MQTT_EYES_TOPIC);

        MQTTClient.subscribe(MQTT_INFO_TOPIC);
        MQTTClient.subscribe(MQTT_IP_TOPIC);
        MQTTClient.subscribe(MQTT_ERROR_TOPIC);
    }
    else
    {
        //set LED off
        digitalWrite(LED_BUILTIN, HIGH);

        Serial.print("failed, rc=");
        Serial.print(MQTTClient.state());
        Serial.println(" try again in 5 seconds");
    }
}

void MessageReceived(char *topic, byte *payload, unsigned int length)
{
#ifdef PRINT_TO_SERIAL
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
#endif

    std::string message = "";

    for (int i = 0; i < length; i++)
    {
        message += (char)payload[i];
    }

#ifdef PRINT_TO_SERIAL
    Serial.println(message.c_str());
#endif

    sendWallECommand(topic, message);
}

void loopMQTTClient()
{
    if (WiFi.isConnected() == false)
    {
        //just do nothing and wait for the reconnection event to happen
        delay(1000);
    }
    else
    {
        //MQTT section
        if (MQTTClient.connected() == false)
        {
            //set LED off
            digitalWrite(LED_BUILTIN, HIGH);

            MQTTConnect();
        }
        else
        {
            //set LED on
            digitalWrite(LED_BUILTIN, LOW);

            if (millis() - previousSendIPMillis >= 1000)
            {
                previousSendIPMillis = millis();

                MQTTClient.publish(MQTT_IP_TOPIC, WiFi.localIP().toString().c_str());
            }
        }
        MQTTClient.loop();
    }
}