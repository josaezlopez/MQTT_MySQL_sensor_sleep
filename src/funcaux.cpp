#include <funcaux.h>



void publicar(PubSubClient& mqttInst,MySQL_Connection& conn_mysql, Adafruit_BME280& bmeInst){
  String temp;
  String press;
  String hum;

  char sql[255];

  temp = String(bmeInst.readTemperature());
  press = String(bmeInst.readPressure() / 100.0F);
  hum = String(bmeInst.readHumidity());

  mqttInst.publish(MQTT_TOPIC_TEMPERATURA,temp.c_str(),true);
  mqttInst.publish(MQTT_TOPIC_PRESION,press.c_str(),true);
  mqttInst.publish(MQTT_TOPIC_HUMEDAD,hum.c_str(),true);
  mqttInst.disconnect();
  
  sprintf(sql,"INSERT INTO %s.%s (fecha, presion, temperatura, humedad) VALUES (now(),%s,%s,%s)",
          MYSQLDB, MYSQLTABLE, press.c_str(), temp.c_str(), hum.c_str());
  
  Serial.println(sql);
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn_mysql);
  cur_mem->execute(sql);
  delete cur_mem;
  

}


/* Callback de recepcion de mensajes */
void recibeTopic(char* topic, byte* payload, unsigned int length) {
 
}


bool WIFIConnect(){
  int n;

  WiFi.begin(SSID, PASSWORD);
  Serial.print("Conectando");
  for(n=0 ;  n<60 ; n++) {
    if(WiFi.status() == WL_CONNECTED)
      break;
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  if(n==60)
    return false;
  //digitalWrite(LED_BUILTIN,HIGH);
  Serial.print("Conectado a ");
  Serial.println(SSID);
  return true;
}
