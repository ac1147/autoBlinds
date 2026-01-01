import serial
import time
import serial.tools.list_ports
from pynput import keyboard
from keyboardTracker import create_tracker #For Push Button Control

# ==============================
# Arduino Setup
# ==============================

ports = serial.tools.list_ports.comports()

arduino_port = None
for port in ports:
    if "usbmodem" in port.device or "usbserial" in port.device:
        arduino_port = port.device
        break

if arduino_port is None:
    raise RuntimeError("Arduino not found")

arduino = serial.Serial(port=arduino_port, baudrate=9600, timeout=1)
time.sleep(2)

# ==============================
# Motor Control
# ==============================

tracker = create_tracker()

while True:
    if tracker.a_pressed:
        arduino.write(b'a')
    elif tracker.d_pressed:
        arduino.write(b'd')
    else:
        arduino.write(b's')

    time.sleep(0.1)


