#include <WiFi.h>            // Librería para la conexión WiFi
#include <time.h>            // Librería para gestionar fecha y hora
#include <stdint.h>          
#include <PubSubClient.h>    // Librería para cliente MQTT

// Configuración de la red WiFi
const char* ssid = "ALUMNOS_CICLOS";        // Nombre de la red WiFi
const char* password = "Ciclos2025sz?";     // Contraseña de la red WiFi

// Configuración del servidor NTP para obtener fecha y hora
const char* ntpServer = "es.pool.ntp.org";      // Servidor de hora NTP
const int32_t gmtOffset_sec = 3600;             // Diferencia horaria respecto a GMT
const int32_t daylightOffset_sec = 0;           // Ajuste por horario de verano

// Estructura para almacenar la información de fecha y hora
struct tm timeinfo;

// Configuración del servidor MQTT
const char* mqtt_username = "Juanjo";           // Usuario MQTT
const char* mqtt_password = "2126";             // Contraseña MQTT
const char* mqtt_server = "broker.emqx.io";     // Dirección del broker MQTT
const int mqtt_port = 1883;                     // Puerto MQTT

// Instancias para la conexión WiFi y el cliente MQTT
WiFiClient espClient;
PubSubClient mqtt_client(espClient);

// Función de callback: se ejecuta cuando llega un mensaje al cliente MQTT
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensaje recibido en el tópico: ");
  Serial.println(topic);

  // Convertir el payload (bytes) en un String
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Mensaje: ");
  Serial.println(message);

  // Comprobar el mensaje recibido y actuar sobre el LED
  if (message == "1") {
    Serial.println("ON");
    digitalWrite(LED_BUILTIN, HIGH); // Encender LED
  }
  else if (message == "0") {
    Serial.println("OFF");
    digitalWrite(LED_BUILTIN, LOW);  // Apagar LED
  }
}

// Función para reconectar al servidor MQTT si la conexión se pierde
void reconnect() {
  while (!mqtt_client.connected()) {
    Serial.print("Conectando a MQTT...");
    String client_id = "esp32-client-" + String(WiFi.macAddress()); 
    if (mqtt_client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Conectado!");
      mqtt_client.subscribe("sensor/boton"); // Suscribirse al tópico "sensor/boton"
    }
    else {
      Serial.print("Error, código: ");
      Serial.println(mqtt_client.state());
      delay(5000); // Esperar antes de reintentar
    }
  }
}

void setup() {
  Serial.begin(115200);           // Inicializar comunicación serie a 115200 baudios
  pinMode(LED_BUILTIN, OUTPUT);   // Definir pin del LED como salida

  // Conexión a WiFi
  Serial.println("Conectando a Wifi...");
  WiFi.begin(ssid, password);               // Inicia conexión a la red WiFi
  
  // Espera hasta que se conecte al WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");    // Imprime un punto cada segundo mientras espera
  }
  Serial.println("\nConexion Wifi establecida.");  // Mensaje cuando se establece la conexión
  Serial.print("Direccion IP: ");
  Serial.println(WiFi.localIP());              // Imprime la IP local asignada al dispositivo

  // Configura la sincronización de hora usando el servidor NTP
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  // Configurar cliente MQTT
  mqtt_client.setServer(mqtt_server, mqtt_port);
  mqtt_client.setCallback(callback); // Asignar la función callback
}

void loop() {
  // Verificar y mantener conexión a MQTT
  if (!mqtt_client.connected()) {
    reconnect();
  }
    mqtt_client.loop(); // Procesar mensajes de MQTT

  // Obtener hora actual
  getLocalTime(&timeinfo);

  // Mostrar fecha y hora en el monitor serie
  Serial.println(&timeinfo, "%d %m %Y %H:%M:%S");

  // Crear un string con la fecha y hora actuales
  String currentTime = String(timeinfo.tm_mday) + "/" + 
                       String(timeinfo.tm_mon + 1) + "/" + 
                       String(timeinfo.tm_year) + "-" + 
                       String(timeinfo.tm_hour) + ":" + 
                       String(timeinfo.tm_min) + ":" + 
                       String(timeinfo.tm_sec);

  // Si el cliente MQTT está conectado, envía un mensaje
  if (mqtt_client.connected()) {
    mqtt_client.publish("sensor/hora", "hola");
  }

  delay(1000); 
}
