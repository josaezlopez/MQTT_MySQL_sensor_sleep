#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <WiFiClient.h>
#include <funcaux.h>


LED* led1 = new LED();
os_timer_t timer;
WiFiClient mqttClient;                //Para la conexion con cloudmqtt
WiFiClient mysqlClient;               //Para la conexion con mysql

MySQL_Connection conn(&mysqlClient);  
PubSubClient mqtt(MQTT_SERVER,MQTT_PORT,recibeTopic,mqttClient);        
Adafruit_BME280 bme;

/*****************************************************************************************************/
/* Funcion callBack del timer.*/
void timerCallback(void *pArg) {
  led1->todo();
}

void duerme(){
  led1->end();
  Serial.println("Entrando en sueño profundo");
  ESP.deepSleep(TIMEWAKE,WAKE_RFCAL); // 20e6 is 20 microseconds
}

/******************************* SETUP ***************************************************************/

void setup() {
  Serial.begin(74880);

  // inicializa la funcion callback del timer, cadad 10 ms
  os_timer_setfn(&timer, timerCallback, NULL);
  os_timer_arm(&timer, 10, true);

  led1->begin(50, 1000, 0, PINLED, HIGH, LOW);
  Serial.begin(74880);


  /* Configura el pin GPIO16, con este pin se despierta el esp8266 */
  /* Hay que configurarlo como salida y estado alto,, sino se quedaba bloqueado durante el arranque... */
  digitalWrite(D0,HIGH);
  pinMode(D0, OUTPUT);

  // Inicia el sensor
  if (!bme.begin(0x76)) {
    Serial.println("No se encuentra el sensor BME280");
    while (1);
  }

  // Si hay conexion wifi se conecta a mysql y mqtt, se publican los datos
  if(WIFIConnect()){
    #ifndef NO_MQTT
      int c = 0;
      while(!mqtt.connect(MQTT_ID, MQTT_USER, MQTT_PASS)) {
       c++;
       delay(1000);
       if(c==10){
          Serial.println("No se puede conectar con el broker de mqtt");
          duerme();
          }
       }
       if(mqtt.connected()){
          Serial.println("Conectado con el servidor MQTT");

       }
    #endif


    int contador=0;
    Serial.println("Conectando a la base de datos.");
    while (conn.connect(IPAddress(ADDRESSMYSQL), 3306, (char* )USER4MYSQL, (char*) PASS4MYSQL) != true) {
      delay(1000);
      Serial.print ( "." );
      if(contador++ > 9){
        Serial.println("No se puede conectar con la BD");
        duerme();
        }
      }
    Serial.println("");
    Serial.println("Connected to MySQL Server!");

    publicar(mqtt,conn,bme);


}

    duerme();

}


void loop() {

}
