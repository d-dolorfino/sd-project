'''
Code based on the 'working4-9_slowDCLK.py' code. Slight changes will be done to the code.

This code will change the registers according to Dr. Abichar's suggestions on 4/8

This code will use the python-periphery library in place of Blinka for digital I/O
'''

'''
Default settings according to V2_19 datasheet.
'''

import time

from smbus import SMBus
from periphery import GPIO

# CCD sensor is on address 0x20 (no strap pins) on I2C bus 2
bus = SMBus(2)

# Set up DATA[7:0] pins
d0 = GPIO("/dev/gpiochip2", 2, "in") # P8_7
d1 = GPIO("/dev/gpiochip2", 3, "in") # P8_8
d2 = GPIO("/dev/gpiochip2", 5, "in") # P8_9
d3 = GPIO("/dev/gpiochip2", 4, "in") # P8_10
d4 = GPIO("/dev/gpiochip1", 13, "in") # P8_11
d5 = GPIO("/dev/gpiochip1", 12, "in") # P8_12
d6 = GPIO("/dev/gpiochip1", 15, "in") # P8_15
d7 = GPIO("/dev/gpiochip0", 26, "in") # P8_14

# Set up the clock signal pins
dclk = GPIO("/dev/gpiochip0", 20, "in") # P9_41
vsync = GPIO("/dev/gpiochip1", 17, "in") # P9_23
hsync = GPIO("/dev/gpiochip3", 19, "in") # P9_27
xsync = GPIO("/dev/gpiochip1", 16, "in") # P9_15

# Hardware shutter
shutter = GPIO("/dev/gpiochip3", 16, "out") # P9_30

### I2C Configurations ###

# 4. Keeps all the clocks active low; set to 0x00
bus.write_byte_data(0x20, 0xCC, 0x00) # Default, sets it all to active low

# 3. 8-bit mode, gated clock, disable I2C in spike filter; set to 0x1D
bus.write_byte_data(0x20, 0xCB, 0x1D) # 8-bit mode, ESM on, gated clock

bus.write_byte_data(0x20, 0xAE, 0x01) # Disable DLL; experiement when data is showing up
bus.write_byte_data(0x20, 0x80, 0x00) # Disable internal MOD clk
bus.write_byte_data(0x20, 0x82, 0x09) # Set PLL FB clock divider
bus.write_byte_data(0x20, 0x85, 0x01) # Set MOD clock to 40 MHz
bus.write_byte_data(0x20, 0x86, 0x04) # Set SEQ clock divider
bus.write_byte_data(0x20, 0x87, 0x00) # Set REFGEN clock divider

# 1. DCLK = 2.5 MHz, set to 0x1F
bus.write_byte_data(0x20, 0x89, 0x1F) # Set TCMI clk to 2.5 MHz
bus.write_byte_data(0x20, 0x8A, 0x01) # Set EE CP clk divider
bus.write_byte_data(0x20, 0x80, 0x3F) # Enable internal MOD clk

# 2. Sequencer control, set bit 6 for DCLK < 10 MHz
bus.write_byte_data(0x20, 0x91, 0x43) # Readout rollover for slower DCLK

# bus.write_byte_data(0x20, 0x7D, 0x04) # Mode control; enable PLL; made it to a separate code
# This does turn on DCLK

# Open a file
fo = open("output.txt", "w")

# Software shutter
bus.write_byte_data(0x20, 0xA4, 0x01)

# Hardware shutter
# shutter.write(True)
# shutter.write(False)

### Image data acquisition ###
while(1):
    while(1):
        if (int(dclk.read()) == 0):
            break
    
    # Wait for data to be ready
    while(1):
        if (int(dclk.read()) == 1):
            break
        
    # Wait until we're at the mid-point
    while(1):
        if (int(dclk.read()) == 0):
            break
    
    # Take the byte sample and save in file
    data0 = str(int(d0.read()))
    data1 = str(int(d1.read()))
    data2 = str(int(d2.read()))
    data3 = str(int(d3.read()))
    data4 = str(int(d4.read()))
    data5 = str(int(d5.read()))
    data6 = str(int(d6.read()))
    data7 = str(int(d7.read()))
    
    bin = data7 + data6 + data5 + data4 + data3 + data2 + data1 + data0
    
    fo.write(str(int(bin,2))) 
    fo.write(' ')
    
    # Wait out high level
    while(1):
        if(int(dclk.read()) == 1):
            break
