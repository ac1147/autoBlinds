import serial
import time

arduino = serial.Serial(port='/dev/tty.usbmodem1101', baudrate=9600, timeout=1)
time.sleep(2)

while True:
    cmd = input("Enter command:").strip()
    if cmd == 'q':
        break
    arduino.write(cmd.encode())
    time.sleep(0.1)
    response = arduino.readline().decode().strip()
    if response:
        print("Arduino says:", response)

arduino.close()

