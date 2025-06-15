#include <Arduino.h>
#include "csk.hpp"
// #include "ook.hpp"



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
  const int RGBPINS[3] ={14, 12, 13};
  const int BUTTON = 34;
  const int Ts = 100;
  const String msg = "Hola mundo";

  // Global variable to store RGB values
  int RGB[4][3];
  // Button variable
  int buttonState = 0; 

  void setup() {
    // Setup button
    pinMode(BUTTON, INPUT);
    // Setup pins and turn off LEDs
    for (int i =0; i < 3; i++) {
      pinMode(RGBPINS[i], OUTPUT);
      digitalWrite(RGBPINS[i], LOW);
    }
    // Calculate colors 
    for (int i = 0; i < 4; i++) {
      int color = CSK::convertCoords(CSK::QCSK[i], CSK::Y);
      RGB[i][0] = (color >> 16) & 0xFF; // Red
      RGB[i][1] = (color >> 8) & 0xFF;  // Green
      RGB[i][2] = color & 0xFF;         // Blue
    }

    // Serial setup
    Serial.begin(9600);

    Serial.print("Colors: ");
    for (int i = 0; i < 4; i++) {
      Serial.println("Color " + String(i) + ": " + String(RGB[i][0]) + " " + String(RGB[i][1]) + " " + String(RGB[i][2]));
    }
  }

  void loop() {
    // Run if button is pressed
    buttonState = digitalRead(BUTTON);
    if (buttonState == HIGH) {
      Serial.println("Sending message: " + msg);
      for (int i = 0; i < msg.length(); i++) {
        CSK::send_char(msg[i], RGBPINS, Ts, RGB);
      }
      // Turn off LEDs
      CSK::turn_off(RGBPINS);
      delay(1000); // Wait for a second before sending the next character
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







