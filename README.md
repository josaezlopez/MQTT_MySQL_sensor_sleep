# ESP8266 MQTT_MySQL_sensor_sleep
DATA LOGGER Sensor BME280 con MySQL y MQTT.

Se usa un esp8266 que toma muestra de la temperatura cada cierto tiempo. Los datos se publican en un servidor MQTT y también se llevan a una tabla de mysql.
La tabla de mysql donde se recogen los datos:

MariaDB [iot]> describe  iot.sensor1;
+-------------+----------+------+-----+---------+-------+
| Field       | Type     | Null | Key | Default | Extra |
+-------------+----------+------+-----+---------+-------+
| fecha       | datetime | NO   | PRI | NULL    |       |
| presion     | int(11)  | YES  |     | NULL    |       |
| temperatura | float    | YES  |     | NULL    |       |
| humedad     | float    | YES  |     | NULL    |       |
+-------------+----------+------+-----+---------+-------+
4 rows in set (0,007 sec)

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

Platformio.ini indica que se compila para nodemcuv2. El led que indica el envio de datos está en D8 (funcaux.h) que se corresponde con el GPIO15.
El prototipo se moto sobre un esp12f alimentdo con una bateria 18650 con un shell de este tipo: https://www.az-delivery.de/es/products/battery-expansion-shield-18650-v3-inkl-usb-kabel Con un tiempo de muestreo de 5 minutos la bateria dura sobre dos meses. que se puede alargar si no se necesita una frecencia de muestreo tan alta.

Modifique el fichero secrets.h con su configuracion.
