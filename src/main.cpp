#include <Arduino.h>
#include <params.hpp>
#include "csk.hpp"
// #include "ook.hpp"



// run if ook.hpp is included
#ifdef OOK
  // Constants
  const int LED = 14, Ts = 100, header_size = 5;
  const int pkg_size = 8, guard_each = 4;
  const int BUTTON = 34;
  // Button variable and line to read
  int buttonState = 0, line = 0; 

  void setup() {
    // Run once
    pinMode(BUTTON, INPUT);
    pinMode(LED, OUTPUT);
    Serial.begin(9600);
  }

  void loop() {
    // Reset count
    if (line >= 21) {
      line *=0;
    }
    // Run if button is pressed
    buttonState = digitalRead(BUTTON);
    if (buttonState == HIGH) {
      delay(5000);
      Serial.println("Sending message: " + message[line]);
      for (int i = 0; i < message[line].length(); i++) {
        Serial.println("Sending character: " + String(message[line][i]));
        OOK::send_char(message[line][i], LED, Ts, guard_each, pkg_size, header_size); 
      }
      digitalWrite(LED, LOW);
      line++;
    }
  }

#endif
// run if csk.hpp is included
#ifdef CSK
  // Constants
  const int RGBPINS[3] ={14, 12, 13};
  const int BUTTON = 34;
  const int Ts = 100;
  const int redo[2] = {12, 16};

  // Global variable to store RGB values
  int RGB[4][3];
  // Button variable
  int buttonState = 0; 
  int line = 0;

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

    // Our default zero is keeping the LED on blue
    analogWrite(RGBPINS[0], RGB[0][0]);
    analogWrite(RGBPINS[1], RGB[0][1]);
    analogWrite(RGBPINS[2], RGB[0][2]);
  }

  void loop() {
    // Run if button is pressed
    buttonState = digitalRead(BUTTON);
    if (buttonState == HIGH) {
      delay(5000);
      Serial.println("Sending message " + String(redo[line]) + " : " + message[redo[line]]);
      for (int i = 0; i < message[redo[line]].length(); i++) {
      // for (int i = 0; i < 5; i++) {
        CSK::send_char(message[redo[line]][i], RGBPINS, Ts, RGB);
      }
      // Turn off LEDs
      CSK::turn_off(RGBPINS, RGB);
      line++;
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







