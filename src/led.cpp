
#include "led.h"

// Constructor
void LED::begin(int tOn, int tOff, int duracion, byte pin,bool estadoEmpieza,bool estadoTermina ) {

  pinMode(pin, OUTPUT);
  this->estadoTermina=estadoTermina;
  digitalWrite(pin, estadoEmpieza);
  this->tOn = tOn;
  this->tOff = tOff;
  this->duracion = duracion;
  this->temporizando = true;
  this->pin = pin;
  this->tAntDuracion = this->tAntTon = this->tAntToff = millis();
}

LED::LED() {
  temporizando = false;
  digitalWrite(pin, this->estadoTermina);
}

void LED::end() {
  digitalWrite(pin, estadoTermina); // Ha temporizado, desactivar y bajar pin
  temporizando = false;
}

// Funcion que conmuta el pin con los tiempos dados
// retorna false si la temporizacion acaba.
bool LED::todo() {
  unsigned long tActual;

  if (!temporizando)
    return true;
  tActual = millis();
  if (duracion != 0) {
    if ((tActual - tAntDuracion) > duracion) {
      end();
      return true;
    }
  }

  if (digitalRead(pin)) {
    if ((tActual - tAntTon) > tOn) {
      digitalWrite(pin,!digitalRead(pin));
      tAntToff = tActual;
      return false;
    }
    else return false;

  }
  else {
    if ((tActual - tAntToff) > tOff) {
      digitalWrite(pin, !digitalRead(pin));
      tAntTon = tActual;
      return false;
    }

  }
  return false;
}

LED::~LED() {
  digitalWrite(this->pin, this->estadoTermina);
  this->temporizando = false;
}
