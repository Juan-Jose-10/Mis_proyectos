#include <DHT.h>

#define red_led 16  // LED Rojo
#define green_led 4   // LED Verde
#define yellow_led 2   // LED Azul
#define DHTPIN 15   // Pin donde está conectado el sensor DHT11
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    pinMode(red_led, OUTPUT);
    pinMode(green_led, OUTPUT);
    pinMode(yellow_led, OUTPUT);
    Serial.begin(115200);
    dht.begin();  // Inicializar el sensor DHT11
}

void loop() {
    float temperatura = dht.readTemperature();  // Leer temperatura en °C
    float humedad = dht.readHumidity();        // Leer humedad en %

    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.print(" °C - Humedad: ");
    Serial.print(humedad);
    Serial.println(" %");

    // Apagar todos los LEDs por defecto
    digitalWrite(red_led, LOW);
    digitalWrite(green_led, LOW);
    digitalWrite(yellow_led, LOW);

    // Encender LEDs según las condiciones
    if (temperatura < 20) {
        digitalWrite(green_led, HIGH);  // LED Verde
    }
    if (temperatura > 15) {
        digitalWrite(yellow_led, HIGH);  // LED Azul
    }
    if (temperatura < 20 && temperatura > 15 && humedad < 50) {
        digitalWrite(red_led, HIGH);  // LED Rojo
    }

    delay(2000);  // Esperar 2 segundos antes de la siguiente lectura
}
