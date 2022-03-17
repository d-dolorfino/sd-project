'''
Code to test data output of CCD
'''

import digitalio
import board
import time

print("Hello from data_test.py!")

d0 = digitalio.DigitalInOut(board.P8_7)
d1 = digitalio.DigitalInOut(board.P8_8)
d2 = digitalio.DigitalInOut(board.P8_9)
d3 = digitalio.DigitalInOut(board.P8_10)
d4 = digitalio.DigitalInOut(board.P8_11)
d5 = digitalio.DigitalInOut(board.P8_12)

d6 = digitalio.DigitalInOut(board.P8_14)
d7 = digitalio.DigitalInOut(board.P8_15)
d8 = digitalio.DigitalInOut(board.P8_16)
d9 = digitalio.DigitalInOut(board.P8_17)
d10 = digitalio.DigitalInOut(board.P8_18)
d11 = digitalio.DigitalInOut(board.P8_26)

while True:
    print("Checking value:")
    print("---------------")
    
    print("d0: " + str(int(d0.value)))
    print("d1: " + str(int(d1.value)))
    print("d2: " + str(int(d2.value)))
    print("d3: " + str(int(d3.value)))
    print("d4: " + str(int(d4.value)))
    print("d5: " + str(int(d5.value)))
    
    print("d6: " + str(int(d6.value)))
    print("d7: " + str(int(d7.value)))
    print("d8: " + str(int(d8.value)))
    print("d9: " + str(int(d9.value)))
    print("d10: " + str(int(d10.value)))
    print("d11: " + str(int(d11.value)))
    
    time.sleep(1)
