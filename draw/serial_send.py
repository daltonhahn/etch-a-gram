import time
import serial

arduino = serial.Serial('', 9600)
time.sleep(1)

f = open("path.txt", "r")
for line if f:
    arduino.write(line)
    time.sleep(0.5)
