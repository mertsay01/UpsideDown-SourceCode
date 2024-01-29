#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial bluetooth(10, 11);
Servo myservo;

bool persoonZit = false;
unsigned long lastHeartbeatTime = 0;
const long heartbeatTimeout = 1000;

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  myservo.attach(9);
  myservo.write(90);
}

void loop() {
  if (bluetooth.available()) {
    String message = bluetooth.readStringUntil('\n');
    message.trim();
    Serial.println("Ontvangen bericht: " + message);

    if (message == "HB") {
      lastHeartbeatTime = millis();
      return;
    }

    if (message == "De persoon zit nu") {
      if (!persoonZit) {
        persoonZit = true;
        myservo.write(180);
        delay(1000);
      }
    } else if (message == "De persoon zit nu niet meer") {
      if (persoonZit) {
        persoonZit = false;
        myservo.write(0);
        delay(1000);
      }
    }
  }

  if (millis() - lastHeartbeatTime > heartbeatTimeout) {
    bluetooth.end();
    bluetooth.begin(9600);
    lastHeartbeatTime = millis();
  }
}
