#include <WiFi.h>            // Librería para la conexión WiFi
#include <time.h>            // Librería para gestionar fecha y hora
#include <stdint.h>          
#include <PubSubClient.h>    // Librería para cliente MQTT

// Configuración de la red WiFi
const char* ssid = "ALUMNOS_CICLOS";        // Nombre de la red WiFi
const char* password = "Ciclos2025sz?";     // Contraseña de la red WiFi

// Configuración del servidor NTP para obtener fecha y hora
const char* ntpServer = "es.pool.ntp.org";  // Servidor de hora NTP
const int32_t gmtOffset_sec = 3600;         // Diferencia horaria respecto a GMT
const int32_t daylightOffset_sec = 0;       // Ajuste por horario de verano

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

void setup() {
  Serial.begin(115200);       // Inicializar comunicación serie a 115200 baudios

  Serial.println("Conectando a Wifi...");
  WiFi.begin(ssid, password); // Inicia conexión a la red WiFi

  // Espera hasta que se conecte al WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("."); // Imprime un punto cada segundo mientras espera
  }

  Serial.println("\nConexion Wifi establecida."); // Mensaje cuando se establece la conexión
  Serial.print("Direccion IP: ");
  Serial.println(WiFi.localIP());  // Imprime la IP local asignada al dispositivo

  // Configura la sincronización de hora usando el servidor NTP
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  // Configura la conexión al broker MQTT
  mqtt_client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  mqtt_client.loop(); // Mantiene la conexión y gestiona mensajes MQTT

  // Obtiene la hora actual del sistema
  getLocalTime(&timeinfo);

  // Imprime la fecha y hora en el formato: día mes año hora:minutos:segundos
  Serial.println(&timeinfo, "%d %m %Y %H:%M:%S");

  // Crea una cadena con la fecha y hora actual
  String currentTime = String(timeinfo.tm_mday) + "/" + 
                       String(timeinfo.tm_mon + 1) + "/" + 
                       String(timeinfo.tm_year) + "-" + 
                       String(timeinfo.tm_hour) + ":" + 
                       String(timeinfo.tm_min) + ":" + 
                       String(timeinfo.tm_sec);

  // Si el cliente MQTT está conectado, envía un mensaje
  if (mqtt_client.connected()) {
    mqtt_client.publish("sensor/hora", "Juanjo");
  }

  delay(1000);
} 
