import time
import paho.mqtt.client as paho
from paho import mqtt

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
    # Decode the payload in Python
    temperature = 26.3
    humidity = 34.3
    conductivity = 57.8
    pHValue = 5.7
    nitrogen = 56.7
    phosphorus = 67.8
    potassium = 45
    waterlevel = 17.3

    # message = ("temp: ", temperature, " humid: ", humidity, " cond: ", conductivity, " pH: ", pHValue, " nitro: ", nitrogen, " phos: ", phosphorus, " pot: ", potassium, " water: ", waterlevel)
    # message = ''.join([str(x) for x in message])

    # a single publish, this can also be done in loops, etc.
    # client.publish("testing", payload=temperature)
    client.publish("temp", payload=temperature)
    client.publish("humidity", payload=humidity)
    client.publish("Conductivity", payload=conductivity)
    client.publish("pH Value", payload=pHValue)
    client.publish("Nitrogen", payload=nitrogen)
    client.publish("Phosphorus", payload=phosphorus)
    client.publish("Potassium", payload=potassium)
    client.publish("Water Level", payload=waterlevel)
    time.sleep(1)

    # subscribe to all topics of encyclopedia by using the wildcard "#"
    client.subscribe("temp/#")
    client.subscribe("humidity/#")
    client.subscribe("Conductivity/#")
    client.subscribe("pH Value/#")
    client.subscribe("Nitrogen/#")
    client.subscribe("Phosphorus/#")
    client.subscribe("Potassium/#")
    client.subscribe("Water Level/#")

    # loop_forever for simplicity, here you need to stop the loop manually
# you can also use loop_start and loop_stop
client.loop_forever()
