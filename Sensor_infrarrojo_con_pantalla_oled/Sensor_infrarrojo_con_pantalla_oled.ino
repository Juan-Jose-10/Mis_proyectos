#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Definir constantes
#define ANCHO_PANTALLA 128 // Ancho pantalla OLED
#define ALTO_PANTALLA 64   // Alto pantalla OLED

#define SENSOR_IR 15       // Pin del sensor infrarrojo de obstáculos

// Objeto de la clase Adafruit_SSD1306
Adafruit_SSD1306 display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, -1);

void setup() {
    pinMode(SENSOR_IR, INPUT);
    Serial.begin(9600);
    delay(100);
    Serial.println("Iniciando pantalla OLED");

    // Iniciar pantalla OLED en la dirección 0x3C
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("Error al iniciar OLED");
        while (true); // Detener ejecución si la OLED no funciona
    }
}

void loop() {
    int sin_obstaculo = digitalRead(SENSOR_IR);  // Leer el sensor IR

    // Limpiar pantalla
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 25);

    if (sin_obstaculo == LOW) {  // Si detecta un obstáculo
        Serial.println("¡Obstáculo detectado!");
        display.println("Obstaculo detectado");
    } else {
        Serial.println("Continua");
        display.println("Continua");
    }

    display.display();  // Mostrar en OLED
    delay(500);  // Pequeño retraso para estabilidad
}