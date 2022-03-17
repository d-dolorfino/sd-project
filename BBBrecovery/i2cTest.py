import time
import board
import digitalio

print("Hello from i2cTest.py!")

led = digitalio.DigitalInOut(board.P8_7)
led.direction = digitalio.Direction.OUTPUT
led.value = 0

while True:
    print( 'Pin value:')
    print( int(led.value) )
    
    print('Enter command:')
    i = input()
    
    if (i == '1'):
        led.value = 1
    if (i == '0'):
        led.value = 0

'''
while True:
    led.value = True
    time.sleep(0.5)
    
    led.value = False
    time.sleep(0.5)
'''
