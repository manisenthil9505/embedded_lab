from flask import Flask, render_template, redirect, url_for
import RPi.GPIO as GPIO
app = Flask(__name__)

# Set up GPIO pins
GPIO.setmode(GPIO.BCM)
LED_PIN = 18  # GPIO pin where LED is connected
GPIO.setup(LED_PIN, GPIO.OUT)

# Turn off the LED initially
GPIO.output(LED_PIN, GPIO.LOW)

# Route for the main page
@app.route('/')
def index():
    return render_template('index.html')

# Route to turn on the LED
@app.route('/on')
def turn_on():
    GPIO.output(LED_PIN, GPIO.HIGH)
    return redirect(url_for('index'))

# Route to turn off the LED
@app.route('/off')
def turn_off():
    GPIO.output(LED_PIN, GPIO.LOW)
    return redirect(url_for('index'))

# Clean up GPIO when app stops
@app.route('/cleanup')
def cleanup():
    GPIO.cleanup()
    return "GPIO Cleaned up!"

if __name__ == "__main__":
    try:
        app.run(host='0.0.0.0', port=5000)
    except KeyboardInterrupt:
        GPIO.cleanup()
