#include <Arduino.h>

#ifndef OOK
#define OOK

void send_header(int led, int Ts, int header_size);
void send_bit(bool bit, int pos, int led, int Ts, int guard_each);
void send_char(char c, int led, int Ts, int guard_each, int pkg_size, int header_size);

#endif