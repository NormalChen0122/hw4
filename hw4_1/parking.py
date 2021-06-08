import serial
import time

# XBee setting
serdev = '/dev/ttyUSB0'
s = serial.Serial(serdev, 9600)

d1 = float(input("Enter d1: "))
d2 = float(input("Enter d2: "))
direction = float(input("Enter direction: "))
print("/parking/run %lf %lf %lf \n\r"%(d1, d2, direction))
# send RPC to remote
s.write(("/parking/run %lf %lf %lf \n\r"%(d1, d2, direction)).encode())
time.sleep(1)
s.close()
