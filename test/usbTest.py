import serial
import time


SERIAL_PORT_Carter = "COM6"  # Could be /dev/ttyACM0, check using 'ls /dev/tty*'
BAUD_RATE = 9600


serialCarter = serial.Serial(SERIAL_PORT_Carter, BAUD_RATE, timeout=1)
time.sleep(2)

serialCarter.flushInput()

numberToSend = "123456\n"
serialCarter.write(numberToSend.encode())

time.sleep(1)

serialCarter.write(b'START\n')

while True:
    response = serialCarter.readline().decode().strip()
    if response:
        print("Arduino:", response)


#Use this ti check if your USB port is correct
# import serial

# try:
#     ser = serial.Serial("COM6", 9600, timeout=1)
#     print("✅ Successfully opened COM6!")
#     ser.close()
# except serial.SerialException as e:
#     print("❌ Error:", e)