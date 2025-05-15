import RPi.GPIO as GPIO
import time

# Set the GPIO mode
GPIO.setmode(GPIO.BCM)

# Set the pin number
led_pin1 = 17
led_pin2 = 27
led_pin3 = 22
led_pin4 = 4
GPIO.setup(led_pin1, GPIO.OUT)
GPIO.setup(led_pin2, GPIO.OUT)
GPIO.setup(led_pin3, GPIO.OUT)
GPIO.setup(led_pin4, GPIO.OUT)

try:
    while True:
        GPIO.output(led_pin1, GPIO.HIGH)
        GPIO.output(led_pin2, GPIO.HIGH)
        GPIO.output(led_pin3, GPIO.HIGH)
        GPIO.output(led_pin4, GPIO.HIGH)
        time.sleep(1)                    
        GPIO.output(led_pin1, GPIO.LOW)
        GPIO.output(led_pin2, GPIO.LOW)
        GPIO.output(led_pin3, GPIO.LOW)
        GPIO.output(led_pin4, GPIO.LOW) 
        time.sleep(1)                    
except KeyboardInterrupt:
    pass
                   
finally:
    GPIO.cleanup()
