// Pin Definitions
const int rainSensorPin = A0; // Pin connected to the rain sensor (analog input)
const int pumpPin = 9;        // Pin connected to the relay controlling the water pump (PWM output)

// Water level thresholds (analog values for the rain sensor)
const int minLevel = 300; // Minimum water level (sensor value range: 0-1023)
const int maxLevel = 700; // Maximum water level (sensor value range: 0-1023)

// Variables
int sensorValue = 0; // Variable to store the rain sensor's value
int pumpSpeed = 0;    // Variable to control the pump speed

void setup() {
  pinMode(rainSensorPin, INPUT); // Set rain sensor pin as input
  pinMode(pumpPin, OUTPUT);      // Set pump pin as output
  
  // Initialize the pump to off
  analogWrite(pumpPin, 0);  
}

void loop() {
  // Read the value from the rain sensor
  sensorValue = analogRead(rainSensorPin);
  
  // Check if the water level has reached or exceeded the minimum level
  if (sensorValue >= minLevel) {
    // If the water level is below maxLevel, pump slowly
    if (sensorValue < maxLevel) {
      // Map the sensor value between minLevel and maxLevel to a pump speed between 50 and 255
      pumpSpeed = map(sensorValue, minLevel, maxLevel, 50, 255);
    }
    // If the water level exceeds maxLevel, pump faster
    else {
      pumpSpeed = 255; // Max speed
    }
    
    // Control the pump speed based on the water level
    analogWrite(pumpPin, pumpSpeed);
  } 
  // If the water level is below the minimum level, stop the pump
  else {
    analogWrite(pumpPin, 0);
  }
  
  // Add a small delay to avoid rapid changes and ensure smooth operation
  delay(500); // Delay in milliseconds
}
