# ESP8266 MQTT_MySQL_sensor_sleep
DATA LOGGER Sensor BME280 con MySQL y MQTT.

Se usa un esp8266 que toma muestra de la temperatura cada cierto tiempo. Los datos se publican en un servidor MQTT y también se llevan a una tabla de mysql.

Para crear la tabla:
create database iot;
use iot;
CREATE TABLE `sensor1` (
  `fecha` datetime NOT NULL,
  `presion` int(11) DEFAULT NULL,
  `temperatura` float DEFAULT NULL,
  `humedad` float DEFAULT NULL,
  PRIMARY KEY (`fecha`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

Platformio.ini indica que se compila para nodemcuv2. El led que indica el envío de datos está en D8 (funcaux.h) que se corresponde con el GPIO15.
El prototipo se monto sobre un esp12f alimentado con una batería 18650 desde un shell de este tipo: https://www.az-delivery.de/es/products/battery-expansion-shield-18650-v3-inkl-usb-kabel Con un tiempo de muestreo de 5 minutos la batería dura sobre dos meses. Se puede alargar la duración de la batería bajando la frecuencia de muestreo.

Modifique el fichero secrets.h con su configuración.
