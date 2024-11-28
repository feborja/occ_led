#include "ook.hpp"

void send_header(int led, int Ts, int header_size) {
  Serial.print("Header");
  digitalWrite(led, HIGH);
  delay(header_size * Ts);
  digitalWrite(led, LOW);
  Serial.print(" Guard ");
  delay(Ts);

}

void send_bit(bool bit, int pos, int led, int Ts, int guard_each) {
  if (pos == guard_each - 1) {
    Serial.print(" Guard ");
    digitalWrite(led, LOW);
    delay(Ts);
  }
  if (bit) {
    Serial.print("1");
    digitalWrite(led, HIGH);
    delay(Ts);
  }
  else {
    Serial.print("0");
    digitalWrite(led, LOW);
    delay(Ts);
  }
};

void send_char(char c, int led, int Ts, int guard_each, int pkg_size, int header_size) {
  send_header(led, Ts, header_size);
  for (int i = pkg_size - 1; i >= 0; i--) {
    // Serial.print(String((c >> i) & 1));
    send_bit((c >> i) & 1, i, led, Ts, guard_each);
  }
  // Turn off LED
  digitalWrite(led, LOW);
  // Guard
  Serial.print(" Guard ");
  delay(Ts);
  Serial.println();
}