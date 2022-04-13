/*
 * Ejemplo de operadores en Lenguaje C
 *
 * Por: Alberto Pacheco
 * Fecha: 11 de abril de 2022
 * 
 * Repaso de lenguaje C en Arduino
 *
 */

// Bibliotecas
#include <iostream>

using namespace std;

using u32 = uint32_t;

// Constantes
const u32 MIN_CONTA = 0x080;
const u32 ITER = 200000;
const u32 INIT_CONTA = 0x08000000;

// Variables
u32 conta = INIT_CONTA;

// Definición de objetos

void setup() {
  // Serial.begin(115200);
  delay(10);
  cout << "Contador de anillo" << endl;
  // delay(500);
} // setup

void loop() {
  // Serial.printf("Contador = %d", conta);
  // cout << "Contador = " << conta << endl;
  // delay(1000);
} // loop
