#include <Arduino.h>
#include <vector>
#include <map>

#ifndef CSK
#define CSK


// Function declarations
/*
# turn_red
@brief Turns the LED red

@param int R_PIN: the pin of the red LED
@param int G_PIN: the pin of the green LED
@param int B_PIN: the pin of the blue LED

@return void
*/
void turn_red(int R_PIN, int G_PIN, int B_PIN);

/*
# turn_green
@brief Turns the LED green

@param int R_PIN: the pin of the red LED
@param int G_PIN: the pin of the green LED
@param int B_PIN: the pin of the blue LED

@return void
*/
void turn_green(int R_PIN, int G_PIN, int B_PIN);

/*
# turn_blue

@brief Turns the LED blue

@param int R_PIN: the pin of the red LED
@param int G_PIN: the pin of the green LED
@param int B_PIN: the pin of the blue LED

@return void
*/
void turn_blue(int R_PIN, int G_PIN, int B_PIN);

/*
# turn_off
@brief Turns the LED off

@param int R_PIN: the pin of the red LED
@param int G_PIN: the pin of the green LED
@param int B_PIN: the pin of the blue LED

@return void
*/
void turn_off(int R_PIN, int G_PIN, int B_PIN);

/*
# turn_white
@brief Turns the LED white

@param int R_PIN: the pin of the red LED
@param int G_PIN: the pin of the green LED
@param int B_PIN: the pin of the blue LED

@return void
*/
void turn_white(int R_PIN, int G_PIN, int B_PIN);

/*
# hex_to_rgb
@brief Converts a hex string to an RGB vector

@param String hex: the hex string to convert

@return std::vector<int>: the RGB vector
*/
std::vector<int> hex_to_rgb(String hex);

/*
# turn_custom
@brief Turns the LED to a custom color

@param int R_PIN: the pin of the red LED
@param int G_PIN: the pin of the green LED
@param int B_PIN: the pin of the blue LED
@param int R: the red value
@param int G: the green value
@param int B: the blue value

@return void
*/
void turn_custom(int R_PIN, int G_PIN, int B_PIN, int R, int G, int B);

// Signal map
extern std::map<int, void(*)(int, int, int)> SIGNAL_MAP;

#endif