/**
 * Arduino Analog I/O controlled by serial commands.
 *
 * Controlling Arduino [Analog Shield](https://store.digilentinc.com/analog-shield-high-performance-add-on-board-for-the-arduino-uno-retired/) with [manual](http://analogshield.com/user-manual.html).
 */

#include <analogShield.h>
#include <CmdMessenger.h>

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

static int sensorValue = 0;        // value read from the pot
static int outputValue = 0;        // value output to the PWM (analog out)
static unsigned int count = 0;

void setup() {
    // initialize serial communications at 9600 bps:
    Serial.begin(9600);
}

void loop() {
    // read the analog in value:
    sensorValue = analogRead(analogInPin);
    // map it to the range of the analog out:
    outputValue = map(sensorValue, 0, 1023, 0, 255);
    // change the analog out value:
    analogWrite(analogOutPin, outputValue);

    // print the results to the serial monitor:
    Serial.print("sensor = " );
    Serial.print(sensorValue);
    Serial.print("\t output = ");
    Serial.println(outputValue);

    // wait 10 milliseconds before the next loop
    // for the analog-to-digital converter to settle
    // after the last reading:
    delay(10);

    count = analog.read(0);  //read in on port labeled 'IN0'
    analog.write(0, count);  //write out the value on port labeled 'OUT0'
}
/* Local Variables: */
/* mode: c++        */
/* End:             */
