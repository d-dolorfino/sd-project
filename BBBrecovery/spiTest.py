import board
import digitalio
import busio

# Set chip select to 0
cs = digitalio.DigitalInOut(board.P9_17)
cs.direction = digitalio.Direction.OUTPUT
cs.value = 0

# Try to create an SPI device
spi = busio.SPI(board.SCLK, board.MOSI, board.MISO)
print("SPI ok!")

spi.write('04')

# spi.readinto(result)

# print(result)
