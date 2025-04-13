#define yellow_led 18
#define BuzzerPin 22   // Pin donde está conectado el buzzer
#define PIRPin 23     // Se coloca un led para mostrar en la foto que el sensor detecta

void setup()
{
    pinMode(yellow_led, OUTPUT);
    pinMode(BuzzerPin, OUTPUT); // Configura el buzzer como salida
    pinMode(PIRPin, INPUT);  //
}

void loop()
{
    if (digitalRead(PIRPin) == HIGH) // Si el PIR detecta movimiento
    {
        digitalWrite(yellow_led, HIGH);   // Enciende el LED
        digitalWrite(BuzzerPin, HIGH); // Enciende el buzzer
    }
    else // Si el PIR NO detecta movimiento
    {
        digitalWrite(yellow_led, LOW);   // Apaga el LED
        digitalWrite(BuzzerPin, LOW); // Apaga el buzzer
    }
}