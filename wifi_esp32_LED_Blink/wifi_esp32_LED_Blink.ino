#include <WiFi.h>

const char* ssid     = "practica5";
const char* password = "123456789";

WiFiServer server(80);

void setup()
{
    Serial.begin(115200);
    pinMode(2, OUTPUT);      

    delay(10);

    
    Serial.println();
    Serial.println();
    Serial.print("Conectando a la RED ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi Conectado.");
    Serial.println("IP Dirección: ");
    Serial.println(WiFi.localIP());
    
    server.begin();

}

void loop(){
 WiFiClient client = server.available();   

  if (client) {                             
    Serial.println("New Client.");           
    String currentLine = "";              
    while (client.connected()) {            
      if (client.available()) {             
        char c = client.read();           
        Serial.write(c);                    
        if (c == '\n') {                   

          if (currentLine.length() == 0) {
            
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            
            client.print("CLIC <a href=\"/H\">AQUI</a> para encender el LED de tu Circuito. <br><br><br>");
            client.print("CLIC <a href=\"/L\">AQUI</a> para apagar el LED de tu circuito.<br>");

           
            client.println();
           
            break;
          } else {    
            currentLine = "";
          }
        } else if (c != '\r') {  
          currentLine += c;      
        }

        
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(2, HIGH);              
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(2, LOW);                
        }
      }
    }
  
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
