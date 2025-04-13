#define pinLedR 18  // LED RGB - ROJO
#define pinLedG 4   // LED RGB - VERDE
#define pinLedB 2   // LED RGB - AZUL
#define fotoresistor 15  // Sensor de luz

int umbralEncendido = 3000;  
int umbralApagado = 2500;    

void setup() {
    pinMode(pinLedR, OUTPUT);
    pinMode(pinLedG, OUTPUT);
    pinMode(pinLedB, OUTPUT);
    pinMode(fotoresistor, INPUT);
    Serial.begin(115200);
}

void loop() {
    int luzValue = analogRead(fotoresistor);  // Leer nivel de luz
    Serial.print("Nivel de luz: ");
    Serial.println(luzValue);

    if (luzValue > umbralEncendido) {  
        // Poca luz -> Encender LED con color específico
        analogWrite(pinLedR, 255);  // Rojo fuerte
        analogWrite(pinLedG, 0);    // Verde apagado
        analogWrite(pinLedB, 0);    // Azul apagado
    } else if (luzValue < umbralApagado) {  
        // Mucha luz -> Apagar LED
        analogWrite(pinLedR, 0);
        analogWrite(pinLedG, 0);
        analogWrite(pinLedB, 0);
    }

    delay(100);  // Pequeño retardo para estabilidad
}