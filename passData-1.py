import time
import serial

arduinoData = serial.Serial('COM3', 115200)
time.sleep(1)

while True:
    while arduinoData.inWaiting() == 0:
        pass
    dataPacket = arduinoData.readline()
    dataPacket = str(dataPacket, 'utf-8')  # makes into data we can understand in python
    dataPacket = dataPacket.strip('\r\n')
    print(dataPacket)

# b -> bytes \r\n -> carriage return new line : lets take care of the data
