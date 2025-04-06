#include <stdint.h>

// Definir pines para los LEDs
uint8_t red_led = 2;   // Pin del LED rojo
uint8_t green_led = 4; // Pin del LED verde

// Variables para los temporizadores para el led rojo y verde
uint64_t previous_millis_red = 0;
uint64_t previous_millis_green = 0;

//  intervalos de tiempo para el led rojo y verde
uint64_t red_interval = 1000;
uint64_t green_interval = 2000;

void setup() {
    // Configurar los pines como salida de cada led
    Serial.begin(9600);
    pinMode(red_led, OUTPUT);
    pinMode(green_led, OUTPUT);

    // Inicializar el estado de cada led, los 2 inician apagados
    digitalWrite(red_led, LOW);
    digitalWrite(green_led, LOW);
}

void loop() {
    uint64_t actual_millis = millis();

    if (actual_millis - previous_millis_red > red_interval) { //Programar el momento en el que enciende el led rojo
        previous_millis_red = millis();
        if (digitalRead(red_led)) {
            digitalWrite(red_led, false);
        } else {
            digitalWrite(red_led, true);
        }
    }

    if (actual_millis - previous_millis_green > green_interval) { //Programar el momento en el que enciende el led verde
        previous_millis_green = millis();
        if (digitalRead(green_led)) {
            digitalWrite(green_led, false);
        } else {
            digitalWrite(green_led, true);
        }
    }
}