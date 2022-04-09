import time
import board
import digitalio

print("Hello from i2cTest.py!")

reset = digitalio.DigitalInOut(board.P9_12)
reset.direction = digitalio.Direction.OUTPUT  

reset.value = 0

while True:
    print( 'P9_12 value: ', int(reset.value))
    
    print('\nEnter pin value:')
    i = input()
    
    if (i == '1'):
        reset.value = 1
    if (i == '0'):
        reset.value = 0
    if (i == 'q'):
        print('Last value of P9_12:', int(reset.value))
        break
