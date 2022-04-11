from smbus import SMBus

bus = SMBus(2)

bus.write_byte_data(0x20, 0x7D, 0x04)
print('PLL on.')
