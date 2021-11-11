#include <Arduino.h>
#include "main.h"

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);

    //set LED off
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
  Serial.println("");
  Serial.println("");

  setupIR();
  setupWifi();
  setupMQTTClient();
}

void loop()
{
  //delay(50); //produces 17-19 messages per second
  delay(100); //produces 9-10 messages per second
  //delay(200); //produces ~5 messages per second

  loopMQTTClient();
}
