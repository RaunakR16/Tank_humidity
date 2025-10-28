#include <dht11.h>
#include <SoftwareSerial.h> // Include the SoftwareSerial library

// Pin definitions
#define DHT11PIN A0   // Define pin A0 for DHT11 sensor
#define RELAY1PIN 7   // Define pin 7 for Fan 1 relay
#define RELAY2PIN 5   // Heat pad
// #define HC05_TX 10    // Define pin 10 as HC-05 TX
// #define HC05_RX 11    // Define pin 11 as HC-05 RX
#define PaperSensorPin A3 // Define pin A3 for the paper sensor

// Sensor and communication objects
dht11 DHT11;
// SoftwareSerial Bluetooth(HC05_TX, HC05_RX); // Create a Bluetooth serial object

// Global variables
bool fan1On = false; // Keeps track of Fan 1 state
bool heatPadOn = false; // Keeps track of Heat Pad state
unsigned long lastToggleTime = 0; // For timing heat pad toggles
const unsigned long heatPadOnDuration = 5000;  // 5 seconds ON
const unsigned long heatPadOffDuration = 3000; // 3 seconds OFF

int PaperSensorValue = 0; // Variable to store paper sensor reading

void setup() {
  Serial.begin(9600);         // Start serial communication for monitoring
  // Bluetooth.begin(9600);      // Start communication with HC-05 module

  pinMode(RELAY1PIN, OUTPUT); // Fan 1 relay
  pinMode(RELAY2PIN, OUTPUT); // Heat pad relay

  digitalWrite(RELAY1PIN, HIGH); // Fan OFF
  digitalWrite(RELAY2PIN, HIGH); // Heat pad OFF
}

void loop() {
  // Read DHT11 sensor
  int chk = DHT11.read(DHT11PIN);
  float humidity = (float)DHT11.humidity;
  float temperature = (float)DHT11.temperature;

  unsigned long currentMillis = millis();

  // Fan control logic
  if (humidity >= 90 && !fan1On) {
    digitalWrite(RELAY1PIN, LOW);  // Fan ON (active low)
    fan1On = true;
    Bluetooth.println("Fan 1 turned ON");
  }
  else if (humidity < 50 && fan1On) {
    digitalWrite(RELAY1PIN, HIGH); // Fan OFF (active low)
    fan1On = false;
    Bluetooth.println("Fan 1 turned OFF");
  }

  // Heat pad control logic
  if (humidity >= 90) {
    if (!heatPadOn && (currentMillis - lastToggleTime >= heatPadOffDuration)) {
      digitalWrite(RELAY2PIN, LOW); // Heat pad ON
      heatPadOn = true;
      lastToggleTime = currentMillis;
    }
    else if (heatPadOn && (currentMillis - lastToggleTime >= heatPadOnDuration)) {
      digitalWrite(RELAY2PIN, HIGH); // Heat pad OFF
      heatPadOn = false;
      lastToggleTime = currentMillis;
    }
  }
  else if (humidity < 50) {
    digitalWrite(RELAY2PIN, HIGH); // Ensure heat pad is OFF
    heatPadOn = false;
  }

  // Read Paper Sensor
  PaperSensorValue = analogRead(PaperSensorPin);

  // Send temperature, humidity, and paper sensor value in CSV format
  Serial.print(temperature, 2);
  Serial.print(",");
  Serial.print(humidity, 2);
  Serial.print(",");
  Serial.println(PaperSensorValue);

  // Send data via Bluetooth
  Bluetooth.print("Humidity: ");
  Bluetooth.print(humidity, 2);
  Bluetooth.println("%");

  Bluetooth.print("Paper Sensor Value: ");
  Bluetooth.println(PaperSensorValue);

  // Delay for sensor stability
  delay(1000);
}
