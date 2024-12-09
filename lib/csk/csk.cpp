#include "csk.hpp"

void turn_red(int R_PIN, int G_PIN, int B_PIN) {
    Serial.println("Turning red");
    digitalWrite(R_PIN, HIGH);
    digitalWrite(G_PIN, LOW);
    digitalWrite(B_PIN, LOW);
}

void turn_green(int R_PIN, int G_PIN, int B_PIN) {
    Serial.println("Turning green");
    digitalWrite(R_PIN, LOW);
    digitalWrite(G_PIN, HIGH);
    digitalWrite(B_PIN, LOW);
}

void turn_blue(int R_PIN, int G_PIN, int B_PIN) {
    Serial.println("Turning blue");
    digitalWrite(R_PIN, LOW);
    digitalWrite(G_PIN, LOW);
    digitalWrite(B_PIN, HIGH);
}

void turn_off(int R_PIN, int G_PIN, int B_PIN) {
    Serial.println("Turning off");
    digitalWrite(R_PIN, LOW);
    digitalWrite(G_PIN, LOW);
    digitalWrite(B_PIN, LOW);
}

void turn_white(int R_PIN, int G_PIN, int B_PIN) {
    Serial.println("Turning white");
    digitalWrite(R_PIN, HIGH);
    digitalWrite(G_PIN, HIGH);
    digitalWrite(B_PIN, HIGH);
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