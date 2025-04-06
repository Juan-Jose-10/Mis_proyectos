#include <stdint.h>

uint8_t red_led = 2;  // LED
uint8_t button1 = 22; // Botón P1
uint8_t button2 = 23; // Botón P2

bool led_state = false;
unsigned long prev_millis = 0;
unsigned long actual_millis = 0;
const unsigned long timeout = 10000; // 10 segundos

void setup() {
    Serial.begin(9600);
    pinMode(red_led, OUTPUT);
    pinMode(button1, INPUT_PULLUP);
    pinMode(button2, INPUT_PULLUP);
    digitalWrite(red_led, LOW);
}

void loop() {
    unsigned long actual_millis = millis();

    if (digitalRead(button1) == LOW) { // Si se presiona P1
        led_state = true;
        prev_millis = actual_millis; // Reinicia el tiempo
        digitalWrite(red_led, HIGH);
    }

    if (digitalRead(button2) == LOW) { // Si se presiona P2
        led_state = false;
        digitalWrite(red_led, LOW);
    }

    if (led_state && (actual_millis - prev_millis >= timeout)) { // Apaga después de 10s
        led_state = false;
        digitalWrite(red_led, LOW);
    }
}