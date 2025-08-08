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

/*
# clamp
@brief Clamp a value between a minimum and maximum range

@param v float: The value to clamp
@param minVal float: The minimum value
@param maxVal float: The maximum value
@return float: The clamped value
*/
float clamp(float v, float minVal = 0.0f, float maxVal = 1.0f);

/*
# fastGammaCorrect
@brief Apply fast gamma correction to a value

@param u float: The value to correct
@return float: The gamma-corrected value
*/
float fastGammaCorrect(float u);

/*
# XYZToRGB
@brief Convert XYZ color space to RGB color space

@param xyz float[3]: The input XYZ color values
@param rgb float[3]: The output RGB color values

@return void
*/
void XYZToRGB(const float xyz[3], float rgb[3]);

/*
# convertCoords
@brief Convert CIE 1931 color space coordinates to QCSK format

@param xy float[2]: The input CIE 1931 color coordinates
@param Y float: The luminance value

@return int: The QCSK color index
*/
int convertCoords(const float xy[2], float Y);

/*
Data sending
*/

/*
# char_to_bits
@brief Convert a char to a list of 2 bits

@param c char: The input character

@return int*: The output list of 2 bits
*/
int* char_to_bits(char c);

/*
# turn_off
@brief Turn off the LEDs

@param led_pins int[3]: The LED pin numbers
@param rgb int[4][3]: The RGB color values

@return void    
*/
void turn_off(const int led_pins[3], int rgb[4][3]);

/*
# send_header
@brief Send the header of the message (all colors in the QCSK format)

@param led_pins int[3]: The LED pin numbers
@param sleep_time int: The sleep time between sending colors
@param rgb int[4][3]: The RGB color values

@return void
*/
void send_header(const int led_pins[3], int sleep_time, int rgb[4][3]);

/*
# send_char
@brief Send a char to the LEDs

@param c char: The input character
@param led_pins int[3]: The LED pin numbers
@param sleep_time int: The sleep time between sending colors
@param rgb int[4][3]: The RGB color values

@return void
*/
void send_char(char c, const int led_pins[3], int sleep_time, int rgb[4][3]);

#endif