#include <Servo.h> // Include servo library
#define SERIESRESISTOR 560    


Servo myServo; // Create a servo object
int servoPin = 9; // Set servo pin
int sensorPin = A0; // Set sensor pin
int sensorVal; // Declare sensor value variable
int potPin = A1; // Set potentiometer pin
int potVal; // Declare potentiometer value variable
int waterSensorPin = A2; // Set water sensor pin
int waterThreshold = 500; // Set water sensor threshold
int servoTime = 30000; // Set servo time to 30 seconds in milliseconds
int ledPin = 13; // Set LED pin
int ledState = LOW; // Set initial LED state
int usPin = 3;
int buzzer = 5;


void setup() {
    myServo.attach(servoPin); // Attach servo to pin
    pinMode(ledPin, OUTPUT); // Set LED pin as output
    pinMode(usPin, OUTPUT);
    pinMode(buzzer,OUTPUT);    

}

void loop() {
  // Get potentiometer value and map to 1-10 minutes
  potVal = analogRead(potPin); // Read potentiometer value
  potVal = map(potVal, 0, 1023, 1, 15); // Map potentiometer value to 1-15 minutes
  if(potVal > 0)
  {
    for(int i = 0; i < servoTime; i++){
      myServo.write(0); // Move servo to 0 degrees
      delay(10); // Wait half of servo time
      i+=10;
      myServo.write(360); // Move servo to 180 degrees
      delay(10); // Wait the other half of servo time
       i+=10;
    }
  }
  // Check water level before running ultrasonic sensor
  if (analogRead(waterSensorPin) > waterThreshold) {
    // Run ultrasonic sensor for selected time
    for (int i = 0; i < potVal && (analogRead(waterSensorPin) > waterThreshold); i++) { // Loop potVal times
      // Code to run ultrasonic sensor here
      digitalWrite(usPin, HIGH); 
    }
  } else {
    // Water level too low, do not run ultrasonic sensor
    // Code to stop ultrasonic sensor here (if applicable)
    tone(buzzer,329);      
    delay(200);
    noTone(buzzer);     
    digitalWrite(usPin, LOW); 
    ledState = HIGH; // Set LED state to high
  }
  digitalWrite(usPin, LOW); 
  digitalWrite(ledPin, ledState); // Write LED state to pin
}
