/*
  SisRefri: Sistema de Refrigeración Manual y Automática
  Ejercicio Código IoT / Diplomado Samsung
  Elaboró: Alberto Pacheco (apacheco@uach.mx)
  Fecha: 20/Abril/2021

  PREMISAS
  1	La refrigeración manual se enciende cada vez que se presione el botón manual
  2	La refrigeración manual tiene prioridad a la refrigeracion automática
  3	Si la temperatura es alta (mayor a 28, por ejemplo), se activa la refrigeración automática
  4	Si tengo alta demanda o sobre carga, se activa la refrigeración automática
  5	Si tengo alta demanda o sobrecarga de funcionamiento y ademas temperatura alta, se activan ambas refrigeraciones

*/

#include <iostream>
#include <cassert>
#include "DHT.h"

using namespace std; // using cout only
using u8 = uint8_t;  // alias for Arduino param type 

const float UMBRAL_TEMP = 29.5; // Valor crítico activación de refrigeración

//// INPUTS
const u8   DHTPIN = 13; // DHT sensor input pin
const u8   B1_MAN = 25; // Button-1 input pin
const u8  B2_ALTA = 26; // Button-2 input pin
const u8 B3_SOBRE = 27; // Button-3 input pin

//// OUTPUTS
const u8 LED_MANUAL = 12; // LED: Refri Manual output
const u8 LED_AUTO   = 14; // LED: Refri Auto output

//// Macro to convert boolean to string
inline string b2s(bool val) { return (val? "on" : "off"); }

//// Temp sensor API
struct Temp {
  const u8 pin;
  float val;
  DHT dht;
  Temp(u8 p): pin(p), dht(p,DHT11) { dht.begin(); } 
  float read() {
    val = dht.readTemperature();
    assert(!isnan(val)); // Failed to read from DHT sensor!
    delay(150);
    return val;
  }
  bool verif() { return val > UMBRAL_TEMP; }
  friend ostream& operator <<(ostream &os, const Temp &t) {
    os << t.val << "C";
    return os; 
  }
};

//// LED API
struct Led {
  const u8 pin;
  bool val;
  Led(u8 p): pin(p) { pinMode(p, OUTPUT); }
  bool operator=(bool state) {
    val = state;
    digitalWrite(pin, val);
    delay(30);
    return val;
  }
  friend ostream& operator <<(ostream &os, const Led &d) {
    os << b2s(d.val);
    return os; 
  }
};

//// Button API
struct Btn {
  const u8 pin;
  bool val = false;
  Btn(u8 p): pin(p) { pinMode(p, INPUT_PULLUP); }
  bool read() {
    val = digitalRead(pin)==LOW;  // inverse-logic
    delay(100);
    return val;
  }
  friend ostream& operator <<(ostream &os, const Btn &b) {
    os << b2s(b.val);
    return os; 
  }
};

/// Devices
Led  led1(LED_MANUAL); // Create manual-ref led-1 
Led  led2(LED_AUTO);   // Create auto-ref led-2 
Btn  btn1(B1_MAN);     // Create manual button-1
Btn  btn2(B2_ALTA);    // Create alta-demanda button-2
Btn  btn3(B3_SOBRE);   // Create sobrecarga button-3
Temp temp(DHTPIN);     // Create temperature sensor

//// Global variables
bool a, b, c, d; // control variables
float old_temp = 0.0; // for temp changes

void read_input(bool start=false) { // get input & set control variables
  if (start) {
    old_temp = temp.read(); // at start read temperature
  }
  a = temp.verif(); // update control variables
  b = btn1.val;
  c = btn2.val;
  d = btn3.val;
}

void control() { // taking action
    led1 = (a && d) || (a && c) || b; // Minimal Form: ad + ac + b
    led2 = a || c || d;               // Minimal Form: a + c + d
}

void report() { // report status
    cout << endl
         << "High Temperature? " << b2s(a) << endl
         << "Btn-Manual = "      << btn1 << endl
         << "Btn-Alta-Dem = "    << btn2 << endl
         << "Btn-Sobrecarga = "  << btn3 << endl;
    cout << ">> MANUAL REFR. = " << led1 << endl;
    cout << ">> AUTOM. REFR. = " << led2 << endl << endl;
}

void setup() {
  led1 = led2 = false; // turn off leds
  //led2 = false; // led-2 auto = off
  cout << "** Sistema de Refrigeración **" << endl;
  read_input(true); // read initial values
  report(); // initial report
}

void loop() {
  if (old_temp != temp.read()) { // read and show temperature if changed
    old_temp = temp.val; // update value
    cout << "Temp = " << temp << endl; // display current temperature
  }
  const auto ch1 = (a != temp.verif()); // read & compare all inputs
  const auto ch2 = (b != btn1.read());
  const auto ch3 = (c != btn2.read());
  const auto ch4 = (d != btn3.read());
  if (ch1 || ch2 || ch3 || ch4) { // Any change?
    read_input(); // read & update control variables
    control();    // take control action
    report();     // show status
  } else { // some delay if no changes...
    delay(500);
  }
}
