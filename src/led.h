#pragma once

#include <Arduino.h>

class LED {
  public:
    LED();
    void begin(int tOn, int tOff, int duracion, byte pin,bool estadoEmpieza=HIGH,bool estadoTermina=HIGH);
    bool todo();
    void end();
    ~LED();

  private:

    unsigned long tOn;
    unsigned long tOff;
    unsigned long duracion;
    bool temporizando;
    unsigned long tAntDuracion;
    unsigned long tAntTon;
    unsigned long tAntToff;
    int pin;
    bool estadoTermina;

};


