'''
Driver code for stepper motor using A4988 driver.
'''
import time

import board
import digitalio

direct = digitalio.DigitalInOut(board.P8_35)
step = digitalio.DigitalInOut(board.P8_38)

direct.direction = digitalio.Direction.OUTPUT
step.direction = digitalio.Direction.OUTPUT

degreeState = 0

def moveByDegree(d, a):
    direct.value = d
    angle = a / 1.8
    
    if(d == '0'):
        degreeState = degreeState + a
    if(d == '1'):
        degreeState = degreeState - a
    
    for i in range(int(angle)):
        step.value = 1
        time.sleep(0.005)
        step.value = 0
        time.sleep(0.005)
    
    time.sleep(1)

while(1):
    userIn0 = input('What direction?: ')
    userIn1 = input('What angle?: ')
    
    moveByDegree(int(userIn0), int(userIn1))
    
    print('')
