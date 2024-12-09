#include <Arduino.h>

#ifndef OOK
#define OOK

// Function declarations

/*
# send_header
@brief Sends the header of the message

@param int led: the pin of the LED
@param int Ts: the time of a bit
@param int header_size: the size of the header

@return void
*/
void send_header(int led, int Ts, int header_size);
/*
# send_bit
@brief Sends a bit of the message

@param bool bit: the bit to be sent
@param int pos: the position of the bit in the message
@param int led: the pin of the LED
@param int Ts: the time of a bit
@param int guard_each: the number of bits to send before a guard bit

@return void
*/
void send_bit(bool bit, int pos, int led, int Ts, int guard_each);
/*
# send_char
@brief Sends a character of the message

@param char c: the character to be sent
@param int led: the pin of the LED
@param int Ts: the time of a bit
@param int guard_each: the number of bits to send before a guard bit
@param int pkg_size: the size of the package
@param int header_size: the size of the header

@return void
*/
void send_char(char c, int led, int Ts, int guard_each, int pkg_size, int header_size);

#endif