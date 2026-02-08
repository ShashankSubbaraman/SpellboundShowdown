import paho.mqtt.client as mqtt
from RPLCD.gpio import CharLCD
import RPi.GPIO as GPIO
import time

lcd = CharLCD(
    numbering_mode=GPIO.BCM,
    pin_rs=26,
    pin_e=19,
    pins_data=[13, 6, 5, 11],
    cols=16,
    rows=2
)
def on_message(client, userdata, msg):
    message = str(msg.payload.decode())
    if message == "cast":
        print("Replaced")
        message = "arc"
    if message == "stab":
        print("replaced")
        message = "line"
    print(f"recieved: {message}")
    lcd.clear()
    lcd.write_string(message[:16])
    if len(message) > 16:
        lcd.cursor_pos = (1, 0)
        lcd.write_string(message[16:32])
    time.sleep(.2)

client = mqtt.Client(client_id="LaptopSubscriber")
client.connect("172.21.114.5")  #pi ip(Broker)
client.subscribe("pi/messages")
client.on_message = on_message

try:
    client.loop_forever()
except KeyboardInterrupt:
    lcd.clear()
    GPIO.cleanup()
