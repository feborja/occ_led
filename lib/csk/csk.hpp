#include <Arduino.h>
#include <cstdio>
#include <cmath>
#include <algorithm>

#ifndef CSK
#define CSK
// Constants

// CIE 1931 color space coordinates for the four colors used in QCSK
const float QCSK[4][2] = {
    {0.169f, 0.007f},  // Should be blue S0 00
    {0.011f, 0.460f},  // Should be cyan S1 01
    {0.734f, 0.265f},  // Should be red S2 10
    {0.402f, 0.597f}   // Should be yellow S3 11
};

const float Y = 1.0f; // Luminance value for conversion

/*
Color conversion to writeable RGB format
*/

float clamp(float v, float minVal = 0.0f, float maxVal = 1.0f);

float fastGammaCorrect(float u);

void XYZToRGB(const float xyz[3], float rgb[3]);

int convertCoords(const float xy[2], float Y);

/*
Data sending
*/

// Transform a char to a int list of 2 bits
int* char_to_bits(char c);

// Turn off the LEDs
void turn_off(const int led_pins[3]);

// Send the header of the message
// The header is all the colors in the QCSK format (an ESC in ascii)
void send_header(const int led_pins[3], int sleep_time, int rgb[4][3]);

// Send a char to the LEDs
// The char is sent in the QCSK format
void send_char(char c, const int led_pins[3], int sleep_time, int rgb[4][3]);

#endif