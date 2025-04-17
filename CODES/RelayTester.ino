int RelayPin = 7;
int RelayPin1 = 5;
void setup() {
	// Set RelayPin as an output pin
	pinMode(RelayPin, OUTPUT);
  pinMode(RelayPin1, OUTPUT);
}

void loop() {
	// Let's turn on the relay...
	digitalWrite(RelayPin, LOW);
  digitalWrite(RelayPin1, HIGH);
	delay(4000);
	
	// Let's turn off the relay...
	digitalWrite(RelayPin, HIGH);
  digitalWrite(RelayPin1, LOW);
	delay(5000);
}
