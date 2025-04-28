#include "csk.hpp"

void turn_red(int R_PIN, int G_PIN, int B_PIN) {
    Serial.println("Turning red");
    analogWrite(R_PIN, HIGH);
    analogWrite(G_PIN, LOW);
    analogWrite(B_PIN, LOW);
}

void turn_green(int R_PIN, int G_PIN, int B_PIN) {
    Serial.println("Turning green");
    analogWrite(R_PIN, LOW);
    analogWrite(G_PIN, HIGH);
    analogWrite(B_PIN, LOW);
}

void turn_blue(int R_PIN, int G_PIN, int B_PIN) {
    Serial.println("Turning blue");
    analogWrite(R_PIN, LOW);
    analogWrite(G_PIN, LOW);
    analogWrite(B_PIN, HIGH);
}

void turn_off(int R_PIN, int G_PIN, int B_PIN) {
    Serial.println("Turning off");
    digitalWrite(R_PIN, LOW);
    digitalWrite(G_PIN, LOW);
    digitalWrite(B_PIN, LOW);
}

void turn_white(int R_PIN, int G_PIN, int B_PIN) {
    Serial.println("Turning white");
    analogWrite(R_PIN, HIGH);
    analogWrite(G_PIN, HIGH);
    analogWrite(B_PIN, HIGH);
}
std::vector<int> hex_to_rgb(String hex) {
    std::vector<int> rgb;
    for (int i = 0; i < 3; i++) {
        String hex_val = hex.substring(i * 2, i * 2 + 2);
        rgb.push_back(strtol(hex_val.c_str(), NULL, 16));
    }
    return rgb;
}

void turn_custom(int R_PIN, int G_PIN, int B_PIN, int R, int G, int B) {
    Serial.println("Turning custom");
    analogWrite(R_PIN, R);
    analogWrite(G_PIN, G);
    analogWrite(B_PIN, B);
}

// Signal map definition
std::map<int, void(*)(int, int, int)> SIGNAL_MAP = {
    {1, turn_red},
    {2, turn_green},
    {3, turn_blue},
    {-1, turn_off},
    {0, turn_white},
};