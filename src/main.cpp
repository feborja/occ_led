#include <Arduino.h>
#include "ook.hpp"

// Constants
const int LED = 13, Ts = 100, header_size = 5;
const int pkg_size = 8, guard_each = 4;
const String msg = "UUU";

// CSK case
const int R_PIN = 13, G_PIN = 12, B_PIN = 14;


void setup() {
  // Run once
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Run forever
  Serial.println("Sending message: " + msg);
  for (int i = 0; i < msg.length(); i++) {
    Serial.println("Sending character: " + String(msg[i]));
    OOK::send_char(msg[i], LED, Ts, guard_each, pkg_size, header_size); 
  }
  digitalWrite(LED, LOW);
}


// Function definitions:

