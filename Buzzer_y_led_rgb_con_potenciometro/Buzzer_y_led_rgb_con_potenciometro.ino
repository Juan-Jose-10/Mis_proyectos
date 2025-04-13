#define red_led 16  // Led RGB - RED
#define purple_led 4   // Led RGB - GREEN
#define white_led 2   // Led RGB - yellow
#define potenciometro 15
#define buzzer 5    // Pin del buzzer

int portValue = 0;
int frecuencia = 0;

void setup() {
    pinMode(red_led, OUTPUT);
    pinMode(purple_led, OUTPUT);
    pinMode(white_led, OUTPUT);
    pinMode(buzzer, OUTPUT);
    Serial.begin(115200);
}

void loop() {
    portValue = analogRead(potenciometro);  
    Serial.print("Potenciometro: ");
    Serial.println(portValue);

    // Mapear el valor del potenciómetro a una frecuencia de 100 a 5000 Hz
    frecuencia = map(portValue, 0, 4095, 100, 5000);  

    Serial.print("Frecuencia: ");
    Serial.println(frecuencia);

    if (portValue >= 865) {
        digitalWrite(red_led, HIGH);
    } else {
        digitalWrite(red_led, LOW);
    }

    if (portValue >= 2030) {
        digitalWrite(purple_led, HIGH);
    } else {
        digitalWrite(purple_led, LOW);
    }

    if (portValue >= 3295) {
        digitalWrite(white_led, HIGH);
    } else {
        digitalWrite(white_led, LOW);
    }

    // Generar el tono según el valor del potenciómetro
    tone(buzzer, frecuencia);
    delay(100);  // Pequeño delay para estabilidad
}