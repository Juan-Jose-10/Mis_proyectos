#include <stdint.h>

uint8_t red_led = 2;  //Se definen la entrada del led
uint8_t button = 23;   //Se define la entrada del pulsador

bool led_state = false;
bool last_button_state = HIGH; // Estado previo del botón

void setup() {
  Serial.begin(9600);

  pinMode(red_led, OUTPUT);    //Salida del led
  pinMode(button, INPUT_PULLUP);  //Señal de entrada del boton

  digitalWrite(red_led, LOW);  
}

void loop() {
  bool current_button_state = digitalRead(button);

  if (current_button_state == LOW && last_button_state == HIGH) { // Detecta solo la transición
    delay(50);  // Antirrebote (manteniendo delay)
    led_state = !led_state;
    digitalWrite(red_led, led_state);
  }

  last_button_state = current_button_state; // Actualiza el estado del botón
}