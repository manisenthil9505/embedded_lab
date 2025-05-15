import tkinter as tk
import RPi.GPIO as GPIO

# Set up GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
LED_PIN = 18
GPIO.setup(LED_PIN, GPIO.OUT)

# Initialize the LED state
led_state = False

# Define the toggle function
def toggle_led():
    global led_state
    if led_state:
        GPIO.output(LED_PIN, GPIO.LOW)
        led_button.config(text="Turn LED ON")
        led_state = False
    else:
        GPIO.output(LED_PIN, GPIO.HIGH)
        led_button.config(text="Turn LED OFF")
        led_state = True

# Create the GUI application
app = tk.Tk()
app.title("LED Toggle")

# Create the button to toggle the LED
led_button = tk.Button(app, text="Turn LED ON", command=toggle_led, font=("Helvetica", 24))
led_button.pack(pady=20)

# Start the GUI loop
app.mainloop()

# Clean up GPIO on exit
GPIO.cleanup()
