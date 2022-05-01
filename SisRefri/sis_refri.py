'''
    sis_refri.py: Sistema de Refrigeración Manual y Automática
    Python for Raspberry Pi Pico
    EJERCICIO DE CLASE PARA OPERADORES LÓGICOS
    Ejercicio Código IoT
    Diplomado Samsung
    Elaboró: Alberto Pacheco (apacheco@uach.mx)
    Fecha: 28/Abril/2021

Based-on: https://github.com/AlbertoPachecoDev/RepasoLengC/blob/main/SisRefri/SisRefri
MicroPy:  https://docs.micropython.org/en/latest/genrst/core_language.html
Firmware: https://micropython.org/download/rp2-pico/
Tutor:    https://projects.raspberrypi.org/en/projects/getting-started-with-the-pico/4
GitHub:   https://github.com/micropython/micropython
Her-Mul:  https://realpython.com/inheritance-composition-python/
If-Arit:  https://book.pythontips.com/en/latest/ternary_operators.html
Rp2-Ref:  https://docs.micropython.org/en/latest/rp2/quickref.html
Fade i/o: https://github.com/micropython/micropython/blob/master/examples/hwapi/soft_pwm2_uasyncio.py
Pin Ref:  https://docs.micropython.org/en/latest/library/machine.Pin.html
DHT11:    https://www.instructables.com/DHT11-With-Raspberry-Pi-Pico/
DHT11:    https://www.hackster.io/robert-thas/temperature-reading-with-rpi-pico-micropython-dd3bc0

from dht11 import *
dht = DHT(18) #temperature and humidity sensor connect to D18 port
t,h = dht.readTempHumid() # read temp & humid
print(f'T: {t}, H: {h}') # debug

CONEXIONES RASPBERRY PI PICO:
  PINS: /Users/albertopacheco-gonzalez/Library/Arduino15/packages/arduino/hardware/mbed_rp2040/3.0.1/variants/RASPBERRY_PI_PICO/pins_arduino.h
  - RPI -> INPUT DHT11 SENSOR
    - VCC/VIN -> VCC
    - GND-PIN -> GND
    - GPIO-13[17] -> SIGNAL
  - RPI INPUT BUTTONS
    - BTN-1: GPIO-10[14]  (MANUAL)
    - BTN-2: GPIO-11[15]  (ALTA-DEMANDA)
    - BTN-3: GPIO-12[16]  (SOBRE-CARGA)
  - RPI -> ULN2003 DRIVER OUTPUT LEDS
    - LED-1: GPIO-14[19] -> DRIVER-IN1
    - LED-2: GPIO-15[20] -> DRIVER-IN2
    - VCC/VIN -> DRIVER-VCC
    - GND-PIN -> DRIVER-GND    
'''

from machine import Pin, Timer
import uasyncio
import utime
from micropython import const
#from dht11 import *

UMBRAL_TEMP = const(29)
DELAY = const(1000)

class SuperPin:
    def __bool__(self): return self.value() == 1
    def __str__(self): return 'on ' if self else 'off'

class Led(SuperPin, Pin):
    def __init__(self, pin=25): super().__init__(pin, Pin.OUT)
    def on(self):  self.value(1)
    def off(self): self.value(0)

class Button(SuperPin, Pin):
    def __init__(self, pin): super().__init__(pin, Pin.IN, Pin.PULL_UP)

async def pwm_cycle(led, duty, cycles):
    duty_off = 20 - duty
    for i in range(cycles):
        if duty:
            led.value(1)
            await uasyncio.sleep_ms(duty)
        if duty_off:
            led.value(0)
            await uasyncio.sleep_ms(duty_off)

async def fade_in_out(led):
    #for _ in range(2): # fade twice
    for i in range(1, 21): # Fade in
        await pwm_cycle(led, i, 2)
    for i in range(20, 0, -1): # Fade out
        await pwm_cycle(led, i, 2)

#dht = DHT(13) #temperature and humidity sensor connect to D13 port
a = Led(13) # dht.temp > UMBRAL_TEMP
b = Led(10) # Button(10)
c = Led(11) # Button(11)
d = Led(12) # Button(12)
led = Led() # on=manual, blinks=auto, fades=auto&man
manual = Led(19)
autom  = Led(20)
timer = Timer()
cnt = 0

def blink(timer):
    global cnt, led
    cnt += 1
    if cnt < 10:
        led.toggle()
    else:
        cnt = 0
        led.value(0)
        timer.deinit() # stops timer

def manual_led():
    global led
    led.value(1)
        
def auto_led():
    global timer
    timer.init(freq=6, mode=Timer.PERIODIC, callback=blink)

def man_auto_led():
    global led
    uasyncio.run(fade_in_out(led))

def setup():
    global a, b, c, d, manual, autom
    a.value(0)
    b.value(0)
    c.value(0)
    d.value(0)
    manual.value(0)
    autom.value(0)
    print('** Sistema de Refrigeración **\n')
    print(f'Umbral de temperatura: {UMBRAL_TEMP}C\n')
    utime.sleep_ms(DELAY)

def control():
    global a, b, c, d, manual, autom
    led1 = (a and d) or (a and c) or b
    led2 = a or c or d
    manual.value(1 if led1 else 0)
    autom.value (1 if led2 else 0)
    print(f'a={a} b={b} c={c} d={d} man={manual} auto={autom}')

## Main
setup()
for _ in range(2):
    for _ in range(2):
        for _ in range(2):
            for _ in range(2):
                control()
                if manual and autom:
                    man_auto_led()
                elif manual:
                    manual_led()
                elif autom:
                    auto_led()
                else:
                    led.value(0)
                utime.sleep_ms(DELAY)
                d.toggle()
            c.toggle()
        b.toggle()
    a.toggle()
print('Done!')
