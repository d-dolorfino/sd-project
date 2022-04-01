'''
Default settings according to V2_19 datasheet.
'''

import time

import board
import digitalio
import busio

from smbus import SMBus

bus = SMBus(2)

# Set GPIO pins
d0 = digitalio.DigitalInOut(board.P8_7)
d1 = digitalio.DigitalInOut(board.P8_8)
d2 = digitalio.DigitalInOut(board.P8_9)
d3 = digitalio.DigitalInOut(board.P8_10)
d4 = digitalio.DigitalInOut(board.P8_11)
d5 = digitalio.DigitalInOut(board.P8_12)
d6 = digitalio.DigitalInOut(board.P8_14)
d7 = digitalio.DigitalInOut(board.P8_15)

dclk = digitalio.DigitalInOut(board.P9_41)
vsync = digitalio.DigitalInOut(board.P9_27)
hsync = digitalio.DigitalInOut(board.P9_23)
xsync = digitalio.DigitalInOut(board.P9_15)

dclk.switch_to_input()
vsync.switch_to_input()
hsync.switch_to_input()
xsync.switch_to_input()

bus.write_byte_data(0x20, 0xCC, 0x00)

bus.write_byte_data(0x20, 0xAE, 0x04) # Enable DLL
bus.write_byte_data(0x20, 0x80, 0x00) # Disable internal clk
bus.write_byte_data(0x20, 0x82, 0x09) # Set PLL FB clock divider
bus.write_byte_data(0x20, 0x85, 0x00) # Set MOD clock to 10 MHz
bus.write_byte_data(0x20, 0x86, 0x04) # Set SEQ clock divider
bus.write_byte_data(0x20, 0x87, 0x00) # Set REFGEN clock divider
bus.write_byte_data(0x20, 0x89, 0x01) # Set TCMI clk to 20 MHz
bus.write_byte_data(0x20, 0x8A, 0x01) # Set EE CP clk divider
bus.write_byte_data(0x20, 0x80, 0x3F) # Enable internal clk

print('Start up done!')

bus.write_byte_data(0x20, 0xA4, 0x01)
print('Start shutter! Data incoming:')
#time.sleep(0.1)
# bus.write_byte_data(0x20, 0xA4, 0x00)

# Open a file
fo = open("output.txt", "w")

while(1):
    if(int(vsync.value) == 1):
        # fo.write('Frame start/end! ')
        if (int(hsync.value == 1)):
             # if (int(dclk.value) == 0):
            data0 = str(int(d0.value))
            data1 = str(int(d1.value))
            data2 = str(int(d2.value))
            data3 = str(int(d3.value))
            data4 = str(int(d4.value))
            data5 = str(int(d5.value))
            data6 = str(int(d6.value))
            data7 = str(int(d7.value))
            
            bin = data7 + data6 + data5 + data4 + data3 + data2 + data1 + data0
            
            # print(hex(int(bin, 2)))
            
            # print(counter)
            # print(hex(int(bin, 2)))
            fo.write(str(int(bin, 2))) 
            fo.write(' ')
            #print(data7, data6, data5, data4, data3, data2, data1, data0)
            # print('')
