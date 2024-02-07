import serial
import time
ser = serial.Serial('COM3', 9600)
ser.flushInput()
buf = bytearray(17)
while (True):
    rx_raw = ser.read(17)  #
    # print("raw:  ")
    # print(rx_raw)
    # print("\n")

    mystring = "";
    for c in rx_raw:
        mystring = mystring + " " + hex(c)
    print("hexed: ")
    print(mystring)
    print("\n")

    while (True):
        # rx_raw = ser.read(32)#
        rx_raw = ser.read(17)  #
        # print("raw:  ")
        # print(rx_raw)
        # print("\n")

        # mystring = "";
        # for c in rx_raw:
        #     mystring = mystring + " " + hex(c)
        # print("hexed: ")
        # print(mystring)
        # print("\n")

        # Convert the hex string to bytes
        payload = rx_raw
        # Decode the payload in Python
        Raw_temperature = (payload[1] << 8) | payload[2]
        temperature = Raw_temperature / 100.0
        Raw_humidity = (payload[3] << 8) | payload[4]
        humidity = Raw_humidity / 100.0
        Raw_conductivity = (payload[5] << 8) | payload[6]
        conductivity = Raw_conductivity / 100.0
        Raw_pHValue = (payload[7] << 8) | payload[8]
        pHValue = Raw_pHValue / 100.0
        Raw_nitrogen =  (payload[9] << 8) | payload[10]
        nitrogen = Raw_nitrogen / 100.0
        Raw_phosphorus = (payload[11] << 8) | payload[12]
        phosphorus = Raw_phosphorus / 100.0
        Raw_potassium = (payload[13] << 8) | payload[14]
        potassium = Raw_potassium / 100.0
        Raw_waterlevel = (payload[15] << 8) | payload[16]
        waterlevel = Raw_waterlevel / 100.0


        # Print or use the decoded value
        print(f'Temperature: {temperature}')
        print(f'Humidity: {humidity}')
        print(f'Conductivity: {conductivity}')
        print(f'pH Value: {pHValue}')
        print(f'Nitrogen: {nitrogen}')
        print(f'Phosphorus: {phosphorus}')
        print(f'Potassium: {potassium}')
        print(f'Water Level: {waterlevel}')

        print("\n")
