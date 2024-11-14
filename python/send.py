import serial
import time

arduino = serial.Serial(port='COM13', baudrate=9600, timeout=.1)



while True:
    x = input("Enter Amper voltage: ")
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(0.05)
    if x == 'b' or 'B':
        break
