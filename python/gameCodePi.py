import serial
import time

# Serial Port Configuration
SERIAL_PORT_Riker = "/dev/ttyUSB0"  # Could be /dev/ttyACM0, check using 'ls /dev/tty*'
SERIAL_PORT_Kome = "/dev/ttyUSB1"  # Could be /dev/ttyACM0, check using 'ls /dev/tty*'
SERIAL_PORT_Carter = "/dev/ttyUSB2"  # Could be /dev/ttyACM0, check using 'ls /dev/tty*'
SERIAL_PORT_Taylor = "/dev/ttyUSB3"  # Could be /dev/ttyACM0, check using 'ls /dev/tty*'

BAUD_RATE = 9600

# Wait for the Arduino to boot
time.sleep(2)

try:
    # Open Serial Connection
    serialRiker = serial.Serial(SERIAL_PORT_Riker, BAUD_RATE, timeout=1)
    serialKome = serial.Serial(SERIAL_PORT_Kome, BAUD_RATE, timeout=1)
    serialCarter = serial.Serial(SERIAL_PORT_Carter, BAUD_RATE, timeout=1)
    serialTaylor = serial.Serial(SERIAL_PORT_Taylor, BAUD_RATE, timeout=1)


    time.sleep(2)  # Allow serial to stabilize

    # Send "START" command to Arduino
    serialRiker.write(b'START\n')
    serialKome.write(b'START\n')
    serialCarter.write(b'START\n')
    serialTaylor.write(b'START\n')

    print("Game started on all 4 Arduino Nanos.")
    gameStatus = [False,False,False,False]
    # Wait for Arduino to respond with "DONE"
    while True:
        if serialRiker.in_waiting > 0:
            response = serialRiker.readline().decode('utf-8').strip()
            println("Arduino Output:" + response)
            if response == "DONE":
                print("Game finished!")
                gameStatus[0] = True

        if serialKome.in_waiting > 0:
            response = serialKome.readline().decode('utf-8').strip()
            println("Arduino Output:" + response)
            if response == "DONE":
                print("Game finished!")
                gameStatus[0] = True

        if all(gameStatus.values()):
            print("All games finished!")
            break

except serial.SerialException as e:
    print(f"Serial error: {e}")

finally:
    # Close Serial Connection
    if 'serialRiker' in locals() and serialRiker.is_open:
        serialRiker.close()
    if 'serialKome' in locals() and serialKome.is_open:
        serialKome.close()
    if 'serialCarter' in locals() and serialCarter.is_open:
        serialCarter.close()
    if 'serialTaylor' in locals() and serialTaylor.is_open:
        serialTaylor.close()