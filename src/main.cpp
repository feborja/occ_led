#include <Arduino.h>
#include "csk.hpp"


// run if ook.hpp is included
#ifdef OOK
  // Constants
  const int LED = 32, Ts = 1000, header_size = 5;
  const int pkg_size = 8, guard_each = 4;
  const String msg = "UU";

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

#endif
// run if csk.hpp is included
#ifdef CSK
  // Constants
  const int R_PIN = 14, G_PIN = 12, B_PIN = 13;
  const int R = 255, G = 255, B = 255;
  const int Ts = 1000;

  void setup() {
    // Run once
    pinMode(R_PIN, OUTPUT);
    pinMode(G_PIN, OUTPUT);
    pinMode(B_PIN, OUTPUT);
    Serial.begin(9600);
  }

  void loop() {
    // Loop between red, green, blue, white
    for (int i = 1; i < 5; i++) {
      SIGNAL_MAP[i](R_PIN, G_PIN, B_PIN);
      delay(Ts);
    }
  }

#endif

// run if neither ook.hpp nor csk.hpp is included
#ifndef OOK
#ifndef CSK
  void setup() {
    // Run once
    Serial.begin(9600);
  }

  void loop() {
    // Run forever
    Serial.println("No libraries included");
    delay(1000);
  }
#endif
#endif







