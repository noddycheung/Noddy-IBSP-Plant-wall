import time
import serial
import paho.mqtt.client as paho
from paho import mqtt

ser = serial.Serial('COM3', 9600)
ser.flushInput()
buf = bytearray(17)


client = paho.Client()
client.connect("localhost", 1883)

# setting callbacks for different events to see if it works, print the message etc.
def on_connect(client, userdata, flags, rc, properties=None):
    """
        Prints the result of the connection with a reasoncode to stdout ( used as callback for connect )

        :param client: the client itself
        :param userdata: userdata is set when initiating the client, here it is userdata=None
        :param flags: these are response flags sent by the broker
        :param rc: stands for reasonCode, which is a code for the connection result
        :param properties: can be used in MQTTv5, but is optional
    """
    print("CONNACK received with code %s." % rc)


# with this callback you can see if your publish was successful
def on_publish(client, userdata, mid, properties=None):
    """
        Prints mid to stdout to reassure a successful publish ( used as callback for publish )

        :param client: the client itself
        :param userdata: userdata is set when initiating the client, here it is userdata=None
        :param mid: variable returned from the corresponding publish() call, to allow outgoing messages to be tracked
        :param properties: can be used in MQTTv5, but is optional
    """
    print("mid: " + str(mid))


# print which topic was subscribed to
def on_subscribe(client, userdata, mid, granted_qos, properties=None):
    """
        Prints a reassurance for successfully subscribing

        :param client: the client itself
        :param userdata: userdata is set when initiating the client, here it is userdata=None
        :param mid: variable returned from the corresponding publish() call, to allow outgoing messages to be tracked
        :param granted_qos: this is the qos that you declare when subscribing, use the same one for publishing
        :param properties: can be used in MQTTv5, but is optional
    """
    print("Subscribed: " + str(mid) + " " + str(granted_qos))


# print message, useful for checking if it was successful
def on_message(client, userdata, msg):
    """
        Prints a mqtt message to stdout ( used as callback for subscribe )

        :param client: the client itself
        :param userdata: userdata is set when initiating the client, here it is userdata=None
        :param msg: the message with topic and payload
    """
    print(msg.topic + " " + str(msg.qos) + " " + str(msg.payload))






while (True):
    rx_raw = ser.read(17)  #

    mystring = "";
    for c in rx_raw:
        mystring = mystring + " " + hex(c)
    print("hexed: ")
    print(mystring)
    print("\n")


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
    waterlevel = Raw_waterlevel

    # print("Temperature: ", temperature)
    # print("Temperature: ", str(temperature))
    message = ("temp: ", temperature, " humid: ", humidity, " cond: ", conductivity, " pH: ", pHValue, " nitro: ", nitrogen, " phos: ", phosphorus, " pot: ", potassium, " water: ", waterlevel)
    message = ''.join([str(x) for x in message])

    # a single publish, this can also be done in loops, etc.
    client.publish("testing", payload=message)
    # client.publish("Humidity: ", payload=str(humidity))
    # client.publish("Conductivity: ", payload=str(conductivity))
    # client.publish("pH Value: ", payload=str(pHValue))
    # client.publish("Nitrogen: ", payload=str(nitrogen))
    # client.publish("Phosphorus: ", payload=str(phosphorus))
    # client.publish("Potassium: ", payload=str(potassium))
    # client.publish("Water Level: ", payload=str(waterlevel))

    # loop_forever for simplicity, here you need to stop the loop manually
# you can also use loop_start and loop_stop
client.loop_forever()
