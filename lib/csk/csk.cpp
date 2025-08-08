#include "csk.hpp"

/*
Color conversion to writeable RGB format
*/

float clamp(float v, float minVal, float maxVal) {
    return std::max(minVal, std::min(maxVal, v));
}

float fastGammaCorrect(float u) {
    if (u <= 0.0031308f) {
        return 12.92f * u;
    } else {
        return 1.055f * powf(u, 1.0f/2.4f) - 0.055f;
    }
}

void XYZToRGB(const float xyz[3], float rgb[3]) {
    // Using sRGB conversion matrix (IEC 61966-2-1)
    rgb[0] =  3.2406f * xyz[0] - 1.5372f * xyz[1] - 0.4986f * xyz[2];
    rgb[1] = -0.9689f * xyz[0] + 1.8758f * xyz[1] + 0.0415f * xyz[2];
    rgb[2] =  0.0557f * xyz[0] - 0.2040f * xyz[1] + 1.0570f * xyz[2];

    // Clamp before gamma correction
    rgb[0] = clamp(rgb[0]);
    rgb[1] = clamp(rgb[1]);
    rgb[2] = clamp(rgb[2]);

    // Gamma correction
    rgb[0] = fastGammaCorrect(rgb[0]);
    rgb[1] = fastGammaCorrect(rgb[1]);
    rgb[2] = fastGammaCorrect(rgb[2]);
}

int convertCoords(const float xy[2], float Y) {
    int RGB[3] = {0, 0, 0};
    float x = xy[0];
    float y = xy[1];

    if (y <= 0.001f) { 
        // Invalid data, return black
        return 0;
    }

    // Calculate XYZ from xyY
    float X = (x / y) * Y;
    float Z = ((1.0f - x - y) / y) * Y;

    float xyz[3] = {X, Y, Z};
    float rgb[3];

    XYZToRGB(xyz, rgb);

    // Final clamp and quantization
    RGB[0] = int(clamp(rgb[0]) * 255.0f + 0.5f);
    RGB[1] = int(clamp(rgb[1]) * 255.0f + 0.5f);
    RGB[2] = int(clamp(rgb[2]) * 255.0f + 0.5f);

    // Pack RGB into a single integer (0xRRGGBB format)
    return (RGB[0] << 16) | (RGB[1] << 8) | RGB[2];
}

/*
Data sending
*/

int* char_to_bits(char c) {
    static int bits[4];
    // Convert char to bits
    bits[0] = (c >> 6) & 3; // First 2 bits
    bits[1] = (c >> 4) & 3; // Second 2 bits
    bits[2] = (c >> 2) & 3; // Third 2 bits
    bits[3] = (c >> 0) & 3; // Fourth 2 bits

    return bits;
}

void turn_off(const int led_pins[3], int rgb[4][3]) {
    // Turn off state (blue)
    analogWrite(led_pins[0], rgb[0][0]);
    analogWrite(led_pins[1], rgb[0][1]);
    analogWrite(led_pins[2], rgb[0][2]);
}

void send_header(const int led_pins[3], int sleep_time, int rgb[4][3]) {
    // The header is a ESC in ascii
    // ESC = 0x1B   // 00 01 10 11
    int* bits = char_to_bits(0x1B);
    // Send all bits
    for (int i = 0; i < 4; i++) {
        analogWrite(led_pins[0], rgb[bits[i]][0]);
        analogWrite(led_pins[1], rgb[bits[i]][1]);
        analogWrite(led_pins[2], rgb[bits[i]][2]);
        delay(sleep_time);
    }
    // Turn off LED (zero state -> blue)
    turn_off(led_pins, rgb);
    // Guard
    delay(sleep_time);
}

void send_char(char c, const int led_pins[3], int sleep_time, int rgb[4][3]) {
    // Send the header
    send_header(led_pins, sleep_time, rgb);
    // Get the bits of the char
    int* bits = char_to_bits(c);
    
    // Send all bits
    for (int i = 0; i < 4; i++) {
        analogWrite(led_pins[0], rgb[bits[i]][0]);
        analogWrite(led_pins[1], rgb[bits[i]][1]);
        analogWrite(led_pins[2], rgb[bits[i]][2]);
        delay(sleep_time);
    }
    // Turn off LED
    turn_off(led_pins, rgb);
    // Guard
    delay(sleep_time);
}
