#include <Arduino.h>

// Constants
const int LED = 13, Ts = 1000, header_size = 5;
const int pkg_size = 8, guard_each = 4;
const String msg = "UUU";

// Function declarations
void send_header();
void send_bit(bool bit, int pos);
void send_char(char c);

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
    send_char(msg[i]); 
  }
  digitalWrite(LED, LOW);
}


// Function definitions:
void send_header() {
  Serial.print("Header");
  digitalWrite(LED, HIGH);
  delay(header_size * Ts);
  digitalWrite(LED, LOW);
  Serial.print(" Guard ");
  delay(Ts);

}

void send_bit(bool bit, int pos) {
  if (pos == guard_each - 1) {
    Serial.print(" Guard ");
    digitalWrite(LED, LOW);
    delay(Ts);
  }
  if (bit) {
    Serial.print("1");
    digitalWrite(LED, HIGH);
    delay(Ts);
  }
  else {
    Serial.print("0");
    digitalWrite(LED, LOW);
    delay(Ts);
  }
};

void send_char(char c) {
  send_header();
  for (int i = pkg_size - 1; i >= 0; i--) {
    // Serial.print(String((c >> i) & 1));
    send_bit((c >> i) & 1, i);
  }
  // Turn off LED
  digitalWrite(LED, LOW);
  Serial.println();
}
