'''
Small program to test UART functionality with BBB. Also, tests HC-05 functionality.
'''

import time

import board
import digitalio
import busio

import serial

# print("Hello from bluetoothUART.py!")

# Set up UART access
uart = serial.Serial(
    port='/dev/ttyO4')
    
# Set up GPIO pins for motor control
m1in1 = digitalio.DigitalInOut(board.P8_8)
m1in1.direction = digitalio.Direction.OUTPUT
m1in1.value = False

m1in2 = digitalio.DigitalInOut(board.P8_10)
m1in2.direction = digitalio.Direction.OUTPUT
m1in2.value = False

m2in3 = digitalio.DigitalInOut(board.P8_12)
m2in3.direction = digitalio.Direction.OUTPUT
m2in3.value = False

m2in4 = digitalio.DigitalInOut(board.P8_14)
m2in4.direction = digitalio.Direction.OUTPUT
m2in4.value = False


# Main code starts here
print("UART configurations:")
print(uart.baudrate)
print(uart.bytesize)
print(uart.parity)
print(uart.stopbits)

print(uart.name)


while True:
    rx_buf = uart.read()
    print( type(rx_buf) )
    print(rx_buf)
    
    s = rx_buf.decode('utf-8')
    print(s)
    #print('b\'1\'')
    
    if (s == 'w'):
        # Move foward
        m1in2.value = 1
        m2in4.value = 1
        
        time.sleep(3)
        
        m1in2.value = 0
        m2in4.value = 0
        
    if (s == 'a'):
        # Left turn
        m1in2.value = 1
        m2in3.value = 1
        
        time.sleep(1)
        
        m1in2.value = 0
        m2in3.value = 0
        
    if (s == 'd'):
        # Right turn
        m1in1.value = 1
        m2in4.value = 1
        
        time.sleep(1)
        
        m1in1.value = 0
        m2in4.value = 0
    
    if (s == 's'):
        # Move backward
        m1in1.value = 1
        m2in3.value = 1
        
        time.sleep(1)
        
        m1in1.value = 0
        m2in3.value = 0
        
    if (s == '0'):
        # Stop movement
        m1in1.value = 0
        m1in2.value = 0
        m2in3.value = 0
        m2in4.value = 0
    if (s == 'q'):
        break
    
    
    '''
    if (s == '1'):
        # print('Match!')
        led.value = 1
    
    if (s == '0'):
        # print('Match!')
        led.value = 0
    
    
    if (len(rx_buf) > 0):
        print(rx_buf)
    else:
        print(0)
    '''
    
    #bytesToRead= uart.inWaiting()
    #uart.read(bytesToRead)
    
    #rx_buf = uart.readline()
 
    #print(bytesToRead)
    
    
    # time.sleep(2)
    
'''
    if (rx_buf == '1')
        led.value = True
    
    if (rx_buf == '0')
        led.value = False
    '''
