/*
 * Ejemplo de operadores en Lenguaje C
 * Por: Alberto Pacheco
 * Fecha: 8 de abril de 2022
 * 
 * Repaso de lenguaje C en Arduino, usando operador módulo para un contador de anillo
 *
 * Plantilla básica: https://github.com/codigo-iot/Estructura_Basica
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
  /// Serial.begin(115200);
  delay(10);
  /// Serial.println("Contador de anillo");


  auto time = micros();
  for (u32 i=0; i<ITER; i++) {
    if (conta < MIN_CONTA) { 
      conta = INIT_CONTA;
    } else {
      conta = conta / 2;
      conta = 2 * (conta + 32);
    }
  }
  auto lapse1 = micros() - time; // TIME1 = 7555 micros

  conta = INIT_CONTA;  
  time = micros();
  for (u32 i=0; i<ITER; i++)
    conta = (conta<MIN_CONTA ? INIT_CONTA : (conta>>1)+32)<<1;
    // OJO: LA DIVISION ES MUY COSTOSA conta %= MAX_CONTA
  auto lapse2 = micros() - time; // TIME2 = 8395 micros

  cout << "Contador de anillo" << endl;
  cout << "Sin módulo = " << lapse1 << " micros" << endl;
  cout << "Usando operador módulo = " << lapse2 << " micros" << endl;
  //delay(500);
} // setup

void loop() {
  /// Serial.printf("Contador = %d", conta);
  /// cout << "Contador = " << conta << endl;
/*
  auto time = micros();
  for (u32 i=0; i<ITER; i++) {
    conta = conta / 2; // DIV = 260 micros
    if (conta > MAX_CONTA) conta = 0;
  }
  auto lapse1 = micros() - time;

  time = micros();
  for (u32 i=0; i<ITER; i++) {
    conta >>= 1; // Div = 252 micros
    if (conta > MAX_CONTA) conta = 0;
    // OJO: LA DIVISION ES MUY COSTOSA conta %= MAX_CONTA; // conta = conta + MAX_CONTA
  }
  auto lapse2 = micros() - time;
  cout << "Sin módulo = " << lapse1 << " micros" << endl;
  cout << "Usando operador módulo = " << lapse2 << " micros" << endl;

  delay(1000);
*/
} // loop
