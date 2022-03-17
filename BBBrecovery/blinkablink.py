'''
A small program use to test out digitalio for BeagleBone Black using Adafruit's
Blinka API Pyhon library.

Communications still need to be tested:
- UART
- I2C
- PWM (for laser modulation?)
'''

import time
import board
import digitalio

print("Hello from blinkablink.py!")

led = digitalio.DigitalInOut(board.P8_12)
led.direction = digitalio.Direction.OUTPUT

while True:
    led.value = True
    time.sleep(0.5)
    cd
    led.value = False
    time.sleep(0.5)
