#pragma once
#define SSID            "mySSID"
#define PASSWORD        "passforWIFI"

// MQTT
#define MQTT_USER       "mqttUser"
#define MQTT_PASS       "mqttPass"
#define MQTT_SERVER     "mqttServer"
#define MQTT_PORT       1883
#define MQTT_ID         "sensor1-id"
#define MQTT_TOPIC_TEMPERATURA  "/Sensor1/temperatura"
#define MQTT_TOPIC_PRESION      "/Sensor1/presion"
#define MQTT_TOPIC_HUMEDAD      "/Sensor1/Humedad"

// MySQL
#define ADDRESSMYSQL    192,168,1,125   // Mysql server address
#define MYSQLDB         "iot"           // Mysql database
#define MYSQLTABLE      "sensor1"       // Mysql table name
#define USER4MYSQL      "usuarioMysql"  // Mysql usuario
#define PASS4MYSQL      "passMysql"     // Mysql pass