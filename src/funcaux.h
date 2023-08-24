#pragma once

#include <Arduino.h>
#include <PubSubClient.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <secret.h>


#include "led.h"


#define PINLED      D8
#define TIMEWAKE    3e8         // 5 Minutos = 300.000.000uS / 1000000 / 60

void recibeTopic(char* topic, byte* payload, unsigned int length);
void publicar(PubSubClient& mqttInst,MySQL_Connection& conn, Adafruit_BME280& bmeInst);
bool WIFIConnect();


