#include <SoftwareSerial.h>

const int ldrPin = A0;
SoftwareSerial bluetooth(10, 11);

bool persoonZit = false;
unsigned long lastDebounceTime = 0;
unsigned long lastHeartbeatTime = 0;
const unsigned long debounceDelay = 1000;
const unsigned long heartbeatInterval = 1000;

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  pinMode(ldrPin, INPUT);
}

void loop() {
  int ldrStatus = analogRead(ldrPin);
  unsigned long currentTime = millis();

  if (currentTime - lastHeartbeatTime > heartbeatInterval) {
    bluetooth.println("HB");
    lastHeartbeatTime = currentTime;
  }

  if (ldrStatus <= 100) {
    if (!persoonZit && (currentTime - lastDebounceTime > debounceDelay)) {
      bluetooth.println("De persoon zit nu");
      Serial.println("De persoon zit nu");
      persoonZit = true;
      lastDebounceTime = currentTime;
    }
  } else {
    if (persoonZit && (currentTime - lastDebounceTime > debounceDelay)) {
      bluetooth.println("De persoon zit nu niet meer");
      Serial.println("De persoon zit nu niet meer");
      persoonZit = false;
      lastDebounceTime = currentTime;
    }
  }
}
