'''
Using Troy's HC-05 off of the power circuit. Working
'''
import serial

mls = serial.Serial('COM12')

print('Currently in: Movement Mode.')
print('Enter W, A, S or D to move the Mobile LiDAR Scanner.')
while(1):
    userIn = input('What is your command?: ')

    if (userIn == 'q'):
        print('Exiting movement mode.')
        mls.write( userIn.encode('utf-8') )
        mls.close()

    print('Command executed.')
    mls.write( userIn.encode('utf-8') )
