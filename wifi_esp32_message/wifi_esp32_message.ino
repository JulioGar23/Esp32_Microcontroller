#include <WiFi.h>             
#include <WebServer.h>

WebServer server(80);

void setup() {
  Serial.begin(115200);
  const char* ssid     = "DELLG5";                        // Nombre de la RED Wifi
  const char* password = "julio1234";                            // Password
  
  Serial.println("Iniciar la conexión a WiFi");
  WiFi.disconnect();
  
  Serial.print("Conectando a  ");
  Serial.println(ssid);
  
  //Conectamos el ESP32 a la red wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  //Intentamos conectarnos a la red
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  //Si logramos conectarnos mostramos la ip a la que nos conectamos
  Serial.println("");
  Serial.println("WiFi Conectado Exitosamente");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  //Si entramos a la raiz mostramos las opciones
  server.on("/", mensaje);
  server.begin();
}
void loop() {
  //
  server.handleClient();
  delay(100);
}

void mensaje()   //Función que responde el sitio web
{
  // http status code 200 = OK
  // http status code 400 = bad request
  // Se llama al mensaje que saldrá en el sitio web
  server.send(200, "text/html", "<h2> Este es un mensaje en HTML desde el ESP32. <br> CUSUR </h2>");
}