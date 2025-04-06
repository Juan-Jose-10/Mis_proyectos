#include <stdint.h>

// Definir pines para los LEDs
uint8_t red_led = 2;     // Pin del LED rojo
uint8_t green_led = 4;   // Pin del LED verde
uint8_t yellow_led = 16; // Pin del LED amarillo

// Variable para manejar el estado del semáforo
uint8_t estado = 0;

// Variable para manejar el tiempo de cambio
uint64_t previous_millis = 0;

// Intervalos de tiempo para cada estado
uint64_t red_interval = 3000;    // 3 segundos
uint64_t yellow_interval = 1000; // 1 segundo
uint64_t green_interval = 3000;  // 3 segundos

void setup() {
    Serial.begin(9600);
    
    // Configurar los pines como salida
    pinMode(red_led, OUTPUT);
    pinMode(green_led, OUTPUT);
    pinMode(yellow_led, OUTPUT);

    // Iniciar el semáforo con la luz roja encendida
    digitalWrite(red_led, HIGH);
    digitalWrite(green_led, LOW);
    digitalWrite(yellow_led, LOW);
}
void loop() {
    uint64_t actual_millis = millis();
    switch (estado) {  //Secuencia de encendido de las luces del semaforo
        case 0: // Enciende led rojo
            if (actual_millis - previous_millis >= red_interval) {
                previous_millis = actual_millis;
                digitalWrite(red_led, LOW);
                digitalWrite(yellow_led, HIGH);
                estado = 1;
            }
            break;
        case 1: // Enciende led amarillo
            if (actual_millis - previous_millis >= yellow_interval) {
                previous_millis = actual_millis;
                digitalWrite(yellow_led, LOW);
                digitalWrite(green_led, HIGH);
                estado = 2;
            }
            break;
            case 2: // Enciende led verde
            if (actual_millis - previous_millis >= green_interval) {
                previous_millis = actual_millis;
                digitalWrite(green_led, LOW);
                digitalWrite(yellow_led, HIGH);
                estado = 3;
            }
            break;
        case 3: // Enciende led amarillo
            if (actual_millis - previous_millis >= yellow_interval) {
                previous_millis = actual_millis;
                digitalWrite(yellow_led, LOW);
                digitalWrite(red_led, HIGH);
                estado = 0;
            }
            break;
    }
}