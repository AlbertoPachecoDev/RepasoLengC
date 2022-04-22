## SisRefri: Sistema de Refrigeración Manual y Automática


EJERCICIO DE CLASE PARA OPERADORES LÓGICOS

Ejercicio Código IoT

Diplomado Samsung

Elaboró: Alberto Pacheco (apacheco@uach.mx)

Fecha: 20/Abril/2021

----

### CONTEXTO (HIPOTÉTICO):
  Sistema de refrigeración de un site (servidores)

### PROBLEMA:
      Implementar la lógica de control necesaria (variables y función control)
    para que a partir de 3 botones y un sensor de temperatura (4 entradas)
    se determinen los dos valores de salida (LEDs), para indicar si se 
    activan o no los sistemas de refrigeración manual y automático del site.

### PREMISAS:
  1. La refrigeración manual se enciende cada vez que se presione el botón manual
  2. La refrigeración manual tiene prioridad a la refrigeracion automática
  3. Si la temperatura es alta (mayor a 28, por ejemplo), se activa la refrigeración automática
  4. Si tengo alta demanda o sobrecarga, se activa la refrigeración automática
  5. Si tengo alta demanda o sobrecarga de funcionamiento y ademas temperatura alta, se activan ambas refrigeraciones

### ESTRATEGIAS / TÉCNICAS:
  - Definir variables-control tipo booleano y crear tabla de verdad (mapeo entradas/salidas)
  - Simplificar la expresión booleana usando técnicas Mapas K (online tool)
  - Simplificar el código definiendo APIs para cada dispositivo usando C++
    - Definir sinónimo de tipo seguro (entero positivo 8-bits, u8) para datos de puertos y valores del hardware  
    - Definir constructores para inicializar sensores y puertos
    - Estandarizar API de lectura (read) que lee, convierte, valida y temporiza los valores de lectura de puertos
    - Redefinir operador-consola (insertor << de cout) y operador-asignación (operator=) para simplificar código
    - Definir proceso de la aplicación en 3 etapas (stages): leer entradas, procesar datos y reportar resultados
  - Simplificar puertos de entrada usando un banco de interruptores ([DIP switch IC](http://ardupiclab.blogspot.com/2020/04/a-dip-switch-for-arduino.html))
  - Simplificar puertos de salida (LEDS) usando un [IC driver ULN2003](https://randomnerdtutorials.com/esp32-stepper-motor-28byj-48-uln2003/)

### CONEXIONES:
  - ESP32 -> INPUT DHT11 SENSOR
    - VCC/VIN -> VCC
    - GND-PIN -> GND
    - GPIO-13 -> SIGNAL
  - ESP32 INPUT BUTTONS
    - BTN-1: GPIO-25  (MANUAL)
    - BTN-2: GPIO-26  (ALTA-DEMANDA)
    - BTN-3: GPIO-27  (SOBRE-CARGA)
  - ESP32 -> ULN2003 DRIVER OUTPUT LEDS
    - LED-1: GPIO-12 -> DRIVER-IN1
    - LED-2: GPIO-14 -> DRIVER-IN2
    - VCC/VIN -> DRIVER-VCC
    - GND-PIN -> DRIVER-GND

![DHT11](https://www.makerguides.com/wp-content/uploads/2019/08/DHT11-3-pin-with-Arduino-UNO-wiring-diagram-schematic-768x369.jpg)

![REFRI-SIS](https://user-images.githubusercontent.com/80423661/164800386-53776dd2-3355-41a1-93cf-d26eda5b4be1.jpg)

### [TABLA DE VERDAD](https://docs.google.com/spreadsheets/d/1NBjuOgz4UKXTvdi8rWU8ktnI30kscC70W1K5dwVMzrM/edit#gid=0)

- ENTRADAS (4):
  - HI-TEMP: Sensor Temperatura DHT11 1=Temp>29, 0=Temp<=29
  - B1-MAN: Modo-manual 1=Button-on, 0=Button-off
  - B1-ALTA: Alta-demanda 1=Button-on, 0=Button-off
  - B1-SOBRE: Sobre-carga 1=Button-on, 0=Button-off
- SALIDAS (2):
  - LED-MAN: Refrigeración manual
  - LED-AUTO: Refrigeración automática


| HI-TEMP | B1-MAN | B2-ALTA | B3-SOBRE | LED-MAN | LED-AUTO |
| :--: | :--: | :--: | :--: | :--: | :--: |
| 0 | 0 | 0 | 0 | 0 | 0 |
| 0 | 0 | 0 | 1 | 0 | 1 |
| 0 | 0 | 1 | 0 | 0 | 1 |
| 0 | 0 | 1 | 1 | 0 | 1 |
| 0 | 1 | 0 | 0 | 1 | 0 |
| 0 | 1 | 0 | 1 | 1 | 1 |
| 0 | 1 | 1 | 0 | 1 | 1 |
| 0 | 1 | 1 | 1 | 1 | 1 |
| 1 | 0 | 0 | 0 | 0 | 1 |
| 1 | 0 | 0 | 1 | 1 | 1 |
| 1 | 0 | 1 | 0 | 1 | 1 |
| 1 | 0 | 1 | 1 | 1 | 1 |
| 1 | 1 | 0 | 0 | 1 | 1 |
| 1 | 1 | 0 | 1 | 1 | 1 |
| 1 | 1 | 1 | 0 | 1 | 1 |
| 1 | 1 | 1 | 1 | 1 | 1 |

-----

## Online minimization of boolean functions tool

### [Truth table](http://tma.main.jp/logic/logic.php?lang=en&type=4&v0=a&v1=b&v2=c&v3=d&00=0&01=0&02=0&03=0&04=1&05=1&06=1&07=1&08=0&09=1&0a=1&0b=1&0c=1&0d=1&0e=1&0f=1)

| a | b | c | d | Output |
| :--: | :--: | :--: | :--: | :--: |
| 0 | 0 | 0 | 0 | 0 |
| 0 | 0 | 0 | 1 | 0 |
| 0 | 0 | 1 | 0 | 0 |
| 0 | 0 | 1 | 1 | 0 |
| 0 | 1 | 0 | 0 | 1 |
| 0 | 1 | 0 | 1 | 1 |
| 0 | 1 | 1 | 0 | 1 |
| 0 | 1 | 1 | 1 | 1 |
| 1 | 0 | 0 | 0 | 0 |
| 1 | 0 | 0 | 1 | 1 |
| 1 | 0 | 1 | 0 | 1 |
| 1 | 0 | 1 | 1 | 1 |
| 1 | 1 | 0 | 0 | 1 |
| 1 | 1 | 0 | 1 | 1 |
| 1 | 1 | 1 | 0 | 1 |
| 1 | 1 | 1 | 1 | 1 |

```
DNF = ~ab~c~d + ~ab~cd + ~abc~d + ~abcd + a~b~cd + a~bc~d + a~bcd + ab~c~d + ab~cd + abc~d + abcd

CNF = (a + b + c + d) (a + b + c + ~d) (a + b + ~c + d) (a + b + ~c + ~d) (~a + b + c + d)

Minimal Form = ad + ac + b
```

————

### [Truth table](http://tma.main.jp/logic/logic.php?lang=en&type=4&v0=a&v1=b&v2=c&v3=d&00=0&01=1&02=1&03=1&04=0&05=1&06=1&07=1&08=1&09=1&0a=1&0b=1&0c=1&0d=1&0e=1&0f=1)

| a | b | c | d | Output |
| :--: | :--: | :--: | :--: | :--: |
| 0 | 0 | 0 | 0 | 0 |
| 0 | 0 | 0 | 1 | 1 |
| 0 | 0 | 1 | 0 | 1 |
| 0 | 0 | 1 | 1 | 1 |
| 0 | 1 | 0 | 0 | 0 |
| 0 | 1 | 0 | 1 | 1 |
| 0 | 1 | 1 | 0 | 1 |
| 0 | 1 | 1 | 1 | 1 |
| 1 | 0 | 0 | 0 | 1 |
| 1 | 0 | 0 | 1 | 1 |
| 1 | 0 | 1 | 0 | 1 |
| 1 | 0 | 1 | 1 | 1 |
| 1 | 1 | 0 | 0 | 1 |
| 1 | 1 | 0 | 1 | 1 |
| 1 | 1 | 1 | 0 | 1 |
| 1 | 1 | 1 | 1 | 1 |

```
DNF = ~a~b~cd + ~a~bc~d + ~a~bcd + ~ab~cd + ~abc~d + ~abcd + a~b~c~d + a~b~cd + a~bc~d + a~bcd + ab~c~d + ab~cd + abc~d + abcd

CNF = (a + b + c + d) (a + ~b + c + d)

Minimal Form = a + c + d
```
