#include <WiFi.h> // Librería para manejar conexión Wi-Fi
#include <time.h> // Librería para manejar fecha y hora
#include <stdint.h>
#include <PubSubClient.h>

// Datos de conexión Wi-Fi
const char* ssid        = "ALUMNOS_CICLOS"; // Nombre de la red Wi-Fi
const char* password    = "Ciclos2025sz?";  // Contraseña de la red Wi-Fi

// Configuración del servidor NTP para obtener fecha y hora
const char* ntpServer   = "es.pool.ntp.org"; // Servidor de hora NTP
const int32_t gmtOffset_sec = 3600; // Diferencia horaria respecto a GMT 
const int32_t daylightOffset_sec = 0; // Ajuste por horario de verano 

// Estructura para almacenar información de fecha y hora
struct tm timeinfo;

void setup() {
  Serial.begin(115200); // Inicializar comunicación serie a 115200 baudios

  Serial.println("Conectando a Wifi..."); // Mensaje informando que empieza la conexión Wi-Fi
  WiFi.begin(ssid, password); // Inicia conexión a la red WiFi

  // Espera hasta que se conecte al WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000); 
    Serial.print("."); // Imprime un punto cada segundo mientras espera
  }

  Serial.println("\nConexion Wifi establecida."); // Mensaje cuando se establece la conexión
  Serial.print("Direccion IP: ");
  Serial.println(WiFi.localIP()); // Imprime la IP local asignada al dispositivo

  // Configura la sincronización de hora usando el servidor NTP
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void loop() {
  // Obtiene la hora actual del sistema
  getLocalTime(&timeinfo);

  // Imprime la fecha y hora en el formato: día mes año hora:minutos:segundos
  Serial.println(&timeinfo, "%d %m %Y %H:%M:%S");

  delay(1000);
}
